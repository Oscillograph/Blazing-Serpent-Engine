#ifndef BSE_RENDERERAPI_H
#define BSE_RENDERERAPI_H

#include <Core.h>
#include <glm/glm.hpp>
#include <renderer/VertexArray.h>

// ===============================================
// RendererAPI class is an interface to allow communication between Renderer class and 
// a certain graphics implementation like DirectX, OpenGL, Metal, Vulkan, etc.
// ===============================================

namespace BSE {
	class RendererAPI {
	public:
		enum class API {
			None = 0,	// no graphics
			OpenGL = 1	// OpenGL
		};
		
	public:
		// to be succeded by API implementations
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const VertexArray* vertexArray) = 0;
		
		inline static API GetAPI() { return s_API; }
		//inline static void SetAPI(API api) { s_API = api; }
		
		static RendererAPI* Create(RendererAPI::API api);
	
	private:
		static API s_API;
	};
}

#endif
