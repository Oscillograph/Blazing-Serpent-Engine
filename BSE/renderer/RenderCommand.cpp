#include <renderer/RenderCommand.h>
#include <platforms/opengl/OpenGLRendererAPI.h>

namespace BSE {
	//RendererAPI* RenderCommand::m_RendererAPI = RendererAPI::Create(RendererAPI::API::OpenGL);
	//RendererAPI* RenderCommand::m_RendererAPI = RendererAPI::Create();
	RendererAPI* RenderCommand::m_RendererAPI = new OpenGLRendererAPI();
}
