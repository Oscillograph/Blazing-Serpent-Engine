#include "Renderer2D.h"

namespace BSE {
	OrthographicCamera* Renderer2D::m_Camera = nullptr;
	ShaderLibrary* Renderer2D::m_ShaderLibrary = nullptr;
	
	ShaderLibrary* Renderer2D::GetShaderLibrary() {
		if (m_ShaderLibrary == nullptr){
			m_ShaderLibrary = new ShaderLibrary;
		}
		return m_ShaderLibrary; 
	}
	
	void Renderer2D::Init(){
		RenderCommand::Init();
	}
	
	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height){
		RenderCommand::SetViewPort(0, 0, width, height);
	}
	
	void Renderer2D::BeginScene(OrthographicCamera* camera){
		Renderer2D::m_Camera = camera;
	}
	
	void Renderer2D::EndScene(){
		
	} 
	
	//<template typename T>
	//void Submit(T thing);
	
	void Renderer2D::Submit(Shader* shader, VertexArray* vertexArray, const glm::mat4& transform){
		shader->Bind();
		//UploadUniformBuffer(shader, "u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		//UploadUniformBuffer(shader, "u_Transform", transform);
		shader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		shader->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
