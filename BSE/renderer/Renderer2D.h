#ifndef BSE_RENDERER2D_H
#define BSE_RENDERER2D_H

#include <Core.h>
#include <renderer/RendererAPI.h>
#include <renderer/RenderCommand.h>
#include <renderer/VertexArray.h>
#include <renderer/Texture.h>
#include <renderer/Shader.h>
#include <renderer/OrthographicCamera.h>

namespace BSE {
	class BSE_API Renderer2D {
	public:
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static ShaderLibrary* GetShaderLibrary();
		
		static void Init();
		static void Shutdown();
		
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene(OrthographicCamera* camera); // TODO: take in parameters like camera, lights, environment, etc.
		static void EndScene(); // 
		
		static void Submit(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
		// static void Flush();
		
		// ----------------------------------------------------------------
		//				2D Specific stuff
		// ----------------------------------------------------------------
		static void DrawFilledRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawFilledQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawTextureRect(const glm::vec2& position, const glm::vec2& size, Texture2D* texture);
		static void DrawTextureQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture);
		static void DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	};
}

#endif
