#ifndef BSE_RENDERCOMMAND_H
#define BSE_RENDERCOMMAND_H

#include <Core.h>
#include <renderer/RendererAPI.h>
// #include <glm/glm.hpp>

namespace BSE {
	class BSE_API RenderCommand {
	public:
		inline static void Init(){
			m_RendererAPI->Init();
		}
		
		inline static void Shutdown(){
			m_RendererAPI->Shutdown();
		}
		
		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
			m_RendererAPI->SetViewPort(x, y, w, h);
		}
		
		inline static void SetClearColor(const glm::vec4& color){
			m_RendererAPI->SetClearColor(color);
		}
		
		inline static void Clear(){
			m_RendererAPI->Clear();
		}
		
		inline static void DrawIndexed(VertexArray* vertexArray, uint32_t indexCount = 0){
			m_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}
		
		inline static void SetAPI(RendererAPI::API api){
			if (m_RendererAPI != nullptr) {
				delete m_RendererAPI;
			}
			m_RendererAPI = RendererAPI::Create(api);
		}
		
		inline static RendererAPI* GetAPI(){
			return m_RendererAPI;
		}
		
	public:
		static RendererAPI* m_RendererAPI;
	};
}

#endif
