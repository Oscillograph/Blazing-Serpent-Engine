#ifndef BSE_OPENGLTEXTURE_H
#define BSE_OPENGLTEXTURE_H

#include <Core.h>
#include <renderer/Texture.h>

namespace BSE {
	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(std::string path);
		~OpenGLTexture2D();
		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }
		virtual void Bind(uint32_t slot = 0) const override;
		
	protected:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
	};
}

#endif
