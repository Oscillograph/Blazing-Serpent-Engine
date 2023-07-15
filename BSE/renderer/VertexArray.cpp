#include <renderer/Renderer.h>
#include <renderer/VertexArray.h>
#include <platforms/opengl/OpenGLVertexArray.h>

namespace BSE {
	VertexArray* VertexArray::Create(){
		switch (Renderer::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			BSE_CORE_TRACE("OpenGL Vertex Array is being created");
			return new OpenGLVertexArray();
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
