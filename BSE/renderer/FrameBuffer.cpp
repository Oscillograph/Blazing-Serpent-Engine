#include <renderer/RendererAPI.h>
#include <renderer/FrameBuffer.h>
#include <platforms/opengl/OpenGLFrameBuffer.h>

namespace BSE {
	FrameBuffer* FrameBuffer::Create(const FrameBufferSpecification& spec){
		switch (RendererAPI::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			// BSE_CORE_TRACE("OpenGL Shader is being created");
			return new OpenGLFrameBuffer(spec);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}


