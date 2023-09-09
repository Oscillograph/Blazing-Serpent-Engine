#include <platforms/opengl/OpenGLFrameBuffer.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	namespace Utils {
		static GLenum TextureTarget(bool multisampled){
			if (multisampled)
				return GL_TEXTURE_2D_MULTISAMPLE;
			else
				return GL_TEXTURE_2D;
		}
		
		static void CreateTextures(bool multisample, uint32_t* texID, uint32_t count){
			glGenTextures(count, texID);
			// glBindTexture(TextureTarget(multisample), &texID);
			// glTexStorage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, w, h, GL_TRUE);
		}
		
		static void BindTexture(bool multisample, uint32_t texID){
			glBindTexture(TextureTarget(multisample), texID);
		}
		
		void AttachColorTexture(uint32_t texID, int samples, GLenum format, uint32_t width, uint32_t height, int index){
			bool multisampled = samples > 1;
			if (multisampled){
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			} else {
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), texID, 0);
			BSE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Texture Framebuffer is incomplete");
		}
		
		void AttachDepthTexture(uint32_t texID, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height){
			bool multisampled = samples > 1;
			if (multisampled){
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			} else {
				// glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), texID, 0);
			BSE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Depth Framebuffer is incomplete");
		}
		
		static bool IsDepthFormat(FrameBufferTextureFormat depth){
			switch (depth) {
				case FrameBufferTextureFormat::DEPTH24STENCIL8: return true; break;
			}
			return false;
		}
	}
	
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec) 
	{
		for (auto format : m_Specification.Attachments.Attachments){
			if (!Utils::IsDepthFormat(format.TextureFormat)) {
				m_ColorAttachmentSpecifications.emplace_back(format);
			} else {
				m_DepthAttachmentSpecification = format;
			}
		}
		// BSE_CORE_INFO("Framebuffer specifications set before creating one");
		
		Invalidate();
		// BSE_CORE_INFO("Framebuffer invalidate first run");
	}
	
	OpenGLFrameBuffer::~OpenGLFrameBuffer(){
		DeleteEverything();
	}
	
	void OpenGLFrameBuffer::DeleteEverything(){
		glDeleteFramebuffers(1, &m_RendererID);
		if (!m_ColorAttachments.empty())
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
		
		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}
	
	void OpenGLFrameBuffer::Invalidate(){
		if (m_RendererID) {
			DeleteEverything();
		}
		// BSE_CORE_INFO("Framebuffer member variables cleared");
		
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
		
		bool multiSample = m_Specification.Samples > 1;
		// Attachments
		if (m_ColorAttachmentSpecifications.size()){
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multiSample, m_ColorAttachments.data(), m_ColorAttachments.size());
			
			for (size_t i = 0; i < m_ColorAttachments.size(); i++){
				Utils::BindTexture(multiSample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat) {
					case FrameBufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, m_Specification.Width, m_Specification.Height, i);
						break;
				}
			}
		}
		// BSE_CORE_INFO("Framebuffer: color textures attached");
		
		if (m_DepthAttachmentSpecification.TextureFormat != FrameBufferTextureFormat::None) {
			Utils::CreateTextures(multiSample, &m_DepthAttachment, 1);
			// BSE_CORE_INFO("Framebuffer>Depth: Create Texture");
			Utils::BindTexture(multiSample, m_DepthAttachment);
			// BSE_CORE_INFO("Framebuffer>Depth: Bind Texture");
			switch (m_DepthAttachmentSpecification.TextureFormat) {
				case FrameBufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
					// BSE_CORE_INFO("Framebuffer>Depth: Attach Texture");
					break;
			}
		}
		// BSE_CORE_INFO("Framebuffer: depth textures attached");
		
		if (m_ColorAttachments.size() > 1){
			BSE_CORE_ASSERT(m_ColorAttachments.size <= 4, "BSE Can't do more than 4 color attachments :(");
			
			GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		} else {
			if (m_ColorAttachments.empty()){
				// only depth passed
				glDrawBuffer(GL_NONE);
			}
		}
		// BSE_CORE_INFO("Framebuffer: draws called");
		
		// got reworked with functions above
		/*
		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 
			0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
			);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
		
		glGenTextures(1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexImage2D(
			GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 
			0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL
			);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
		
		BSE_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE), "Framebuffer is incomplete");
		*/
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void OpenGLFrameBuffer::Bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0.0f, 0.0f, m_Specification.Width, m_Specification.Height);
	}
	void OpenGLFrameBuffer::Unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	
	void OpenGLFrameBuffer::Resize(const glm::vec2& size) {
		m_Specification.Width = (uint32_t)roundf(size.x);
		m_Specification.Height = (uint32_t)roundf(size.y);
		Invalidate();
	}
}
