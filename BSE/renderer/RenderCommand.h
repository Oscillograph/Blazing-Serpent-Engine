#ifndef BSE_RENDERCOMMAND_H
#define BSE_RENDERCOMMAND_H

#include <Core.h>
#include <renderer/RendererAPI.h>
#include <glm/glm.hpp>

namespace BSE {
	class BSE_API RenderCommand {
	public:
		inline static void Init(){
			m_RendererAPI->Init();
		}
		
		inline static void SetClearColor(const glm::vec4& color){
			m_RendererAPI->SetClearColor(color);
		}
		
		inline static void Clear(){
			m_RendererAPI->Clear();
		}
		
		inline static void DrawIndexed(VertexArray* vertexArray){
			m_RendererAPI->DrawIndexed(vertexArray);
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
