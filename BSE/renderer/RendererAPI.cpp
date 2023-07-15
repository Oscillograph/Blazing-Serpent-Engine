#include <renderer/RendererAPI.h>
#include <platforms/opengl/OpenGLRendererAPI.h>

namespace BSE {
	// select OpenGL as API
	// RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::None;
	
	
	RendererAPI* RendererAPI::Create(RendererAPI::API api){
		switch (api){
		case RendererAPI::API::None:
			RendererAPI::s_API = RendererAPI::API::None;
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			RendererAPI::s_API = RendererAPI::API::OpenGL;
			BSE_CORE_TRACE("OpenGL Renderer API is called");
			return new OpenGLRendererAPI();
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
	
}


