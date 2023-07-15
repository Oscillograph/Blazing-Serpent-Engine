#include <renderer/Buffer.h>
//#include <log.h>
#include <renderer/Renderer.h>
#include <platforms/opengl/OpenGLBuffer.h>

namespace BSE {
	
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
		switch (Renderer::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			BSE_CORE_TRACE("OpenGL Vertex Buffer is being created");
			return new OpenGLVertexBuffer(vertices, size);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
		switch (Renderer::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
