#ifndef BSE_OPENGLRENDERERAPI_H
#define BSE_OPENGLRENDERERAPI_H

#include <Core.h>
#include <renderer/RendererAPI.h>

namespace BSE {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		OpenGLRendererAPI();
		~OpenGLRendererAPI();
		
		virtual void Init() override;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;
		
		virtual void DrawIndexed(const VertexArray* vertexArray) override;
	};
}


#endif
