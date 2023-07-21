#ifndef BSE_RENDERER_H
#define BSE_RENDERER_H

#include <Core.h>
#include <renderer/RendererAPI.h>
#include <renderer/RenderCommand.h>
#include <renderer/VertexArray.h>
#include <renderer/Texture.h>
#include <renderer/Shader.h>
#include <renderer/OrthographicCamera.h>

namespace BSE {
	class BSE_API Renderer {
	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		//inline static void SetAPI(RendererAPI::API API) { RenderCommand::SetAPI(API);}
		
		static void Init();
		
		static void BeginScene(OrthographicCamera* camera); // TODO: take in parameters like camera, lights, environment, etc.
		static void EndScene(); // 
		
		//<template typename T>
		//static void Submit(T thing);
		static void Submit(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		
		// static void Flush();
	
	private:
		static OrthographicCamera* m_Camera;
	};
	
}

#endif
