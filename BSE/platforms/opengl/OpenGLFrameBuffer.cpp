#include <platforms/opengl/OpenGLFrameBuffer.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
		:m_Specification(spec) 
	{
		Invalidate();
	}
	
	OpenGLFrameBuffer::~OpenGLFrameBuffer(){
		DeleteEverything();
	}
	
	void OpenGLFrameBuffer::DeleteEverything(){
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}
	
	void OpenGLFrameBuffer::Invalidate(){
		if (m_RendererID) {
			DeleteEverything();
		}
		
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
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
