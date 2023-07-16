#include <Core.h>
#include <renderer/Renderer.h>

namespace BSE {
	OrthographicCamera* Renderer::m_Camera = nullptr;
	
	void Renderer::BeginScene(OrthographicCamera* camera){
		m_Camera = camera;
	}
	
	void Renderer::EndScene(){
		
	} 
	
	//<template typename T>
	//void Submit(T thing);
	
	void Renderer::Submit(ShaderExample* shader, VertexArray* vertexArray, const glm::mat4& transform){
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		shader->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
