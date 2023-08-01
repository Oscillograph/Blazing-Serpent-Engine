#include <platforms/opengl/OpenGLTexture.h>
#include <Glad/include/glad/glad.h>
#include <stb_image.h>

namespace BSE {
	OpenGLTexture2D::OpenGLTexture2D(std::string path)
	: m_Path(path)
	{
		//BSE_CORE_INFO("Enter OpenGL Texture2D Constructor");
		int width, height, channels;
		m_RendererID = 0;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		BSE_CORE_ASSERT(data, "Failed to load image from: {0}", path);
		
		GLenum internalFormat = GL_RGB8;
		GLenum dataFormat = GL_RGB8;
		
		if (channels == 4){
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if (channels == 3){
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;
		
		BSE_CORE_ASSERT(((internalFormat == 0) && ( dataFormat == 0)), "Image format is not supported");
		
		//BSE_CORE_INFO("stbi_load successful");
		m_Width = width;
		m_Height = height;
		//BSE_CORE_INFO("width and height set");
		
		glGenTextures(1, &m_RendererID);
		//BSE_CORE_INFO("glGenTextures successful");
		
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		//BSE_CORE_INFO("glBindTexture successful");
		
		// what to do if the texture doesn't fit the place
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//BSE_CORE_INFO("glTexParameteri x2 successful");
		
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		//BSE_CORE_INFO("glTexImage2D successful");
		
		stbi_image_free(data);
		// BSE_CORE_INFO("stbi_image_free successful");
	}
	
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height){
		//BSE_CORE_INFO("Enter OpenGL Texture2D Constructor");
		m_RendererID = 0;
		
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
		//BSE_CORE_INFO("stbi_load successful");
		m_Width = width;
		m_Height = height;
		
		glGenTextures(1, &m_RendererID);
		//BSE_CORE_INFO("glGenTextures successful");
		
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		//BSE_CORE_INFO("glBindTexture successful");
		
		// what to do if the texture doesn't fit the place
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//BSE_CORE_INFO("glTexParameteri x2 successful");
	}
	
	OpenGLTexture2D::~OpenGLTexture2D(){
		glDeleteTextures(1, &m_RendererID);
	}
	
	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
		//BSE_CORE_INFO("glTexImage2D successful");
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const {
		// bind to slot 0
		// glBindTextureUnit(slot, m_RendererID);
		// glBindTexture(slot, m_RendererID);
		glActiveTexture(GL_TEXTURE0 + slot); // for batch texture renderer
		// glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		// BSE_INFO("Texture is bound to: {0}", GL_TEXTURE0 + slot);
	}
	
	void OpenGLTexture2D::Unbind(uint32_t slot) const {
		glActiveTexture(GL_TEXTURE0 + slot); // for batch texture renderer
		// glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		// BSE_INFO("Texture is unbound from: {0}", GL_TEXTURE0 + slot);
	}
	
}
