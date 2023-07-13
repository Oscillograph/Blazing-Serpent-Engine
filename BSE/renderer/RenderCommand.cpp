#include <renderer/RenderCommand.h>
#include <platforms/opengl/OpenGLRendererAPI.h>

namespace BSE {
	// No Renderer API by default, and m_RendererAPI equals nullptr !
	RendererAPI* RenderCommand::m_RendererAPI = RendererAPI::Create(RendererAPI::API::None);
}
