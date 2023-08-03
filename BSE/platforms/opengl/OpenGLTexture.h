#ifndef BSE_OPENGLTEXTURE_H
#define BSE_OPENGLTEXTURE_H

#include <Core.h>
#include <renderer/Texture.h>
// #include <Glad/include/glad/glad.h>

namespace BSE {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(std::string path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();
		virtual void SetData(void* data, uint32_t size) override;
		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }
		inline virtual uint32_t GetID() const override { return m_RendererID; };
		virtual void Bind(uint32_t slot = 0) const override;
		virtual void Unbind(uint32_t slot = 0) const override;
		
		virtual bool operator==(const Texture* other) const override {
			return (m_RendererID == ((OpenGLTexture2D*)other)->m_RendererID);
		}
	protected:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		uint32_t m_InternalFormat;
		uint32_t m_DataFormat;
	};
}

#endif
