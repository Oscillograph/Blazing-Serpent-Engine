#ifndef BSE_RENDERER_H
#define BSE_RENDERER_H

#include <Core.h>
#include <renderer/RendererAPI.h>
#include <renderer/RenderCommand.h>
#include <renderer/VertexArray.h>
#include <renderer/Texture.h>
#include <renderer/Shader.h>
#include <renderer/OrthographicCamera.h>
#include <renderer/GeneralCamera.h>

// sub-modules
#include <renderer/Renderer2D.h>

namespace BSE {
	class BSE_API Renderer {
	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		//inline static void SetAPI(RendererAPI::API API) { RenderCommand::SetAPI(API);}
		static ShaderLibrary* GetShaderLibrary();
		
		static void Init();
		static void Clear(const glm::vec4& color);
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(GeneralCamera* camera); // TODO: take in parameters like camera, lights, environment, etc.
		static void EndScene(); // 
		
		//<template typename T>
		//static void Submit(T thing);
		static void Submit(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		
		// static void Flush();
	
	private:
		static GeneralCamera* m_Camera;
		static ShaderLibrary* m_ShaderLibrary;
	};
	
}

#endif
