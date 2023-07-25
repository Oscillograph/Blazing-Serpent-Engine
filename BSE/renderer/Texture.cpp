#include <renderer/Texture.h>
#include <renderer/RendererAPI.h>
#include <platforms/opengl/OpenGLTexture.h>

namespace BSE {
	Texture2D* Texture2D::Create(std::string path){
		switch (RendererAPI::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			//BSE_CORE_TRACE("OpenGL Texture is being created");
			return new OpenGLTexture2D(path);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	Texture2D* Texture2D::Create(uint32_t width, uint32_t height){
		switch (RendererAPI::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			//BSE_CORE_TRACE("OpenGL Texture is being created");
			return new OpenGLTexture2D(width, height);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}


