#include <Core.h>
#include <renderer/Renderer.h>

namespace BSE {
	OrthographicCamera* Renderer::m_Camera = nullptr;
	ShaderLibrary* Renderer::m_ShaderLibrary = nullptr;
	
	ShaderLibrary* Renderer::GetShaderLibrary() {
		if (m_ShaderLibrary == nullptr){
			m_ShaderLibrary = new ShaderLibrary;
		}
		return m_ShaderLibrary; 
	}
	
	void Renderer::Init(){
		RenderCommand::Init();
		Renderer2D::Init();
	}
	
	void Renderer::Shutdown(){
		// RenderCommand::Shutdown();
		Renderer2D::Shutdown();
	}
	
	void Renderer::OnWindowResize(uint32_t width, uint32_t height){
		RenderCommand::SetViewPort(0, 0, width, height);
	}
	
	void Renderer::BeginScene(OrthographicCamera* camera){
		Renderer::m_Camera = camera;
	}
	
	void Renderer::EndScene(){
		
	} 
	
	//<template typename T>
	//void Submit(T thing);
	
	void Renderer::Submit(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform){
		shader->Bind();
		//UploadUniformBuffer(shader, "u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		//UploadUniformBuffer(shader, "u_Transform", transform);
		shader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		shader->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
