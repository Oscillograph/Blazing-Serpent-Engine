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
	
	void Renderer::Submit(ShaderExample* shader, VertexArray* vertexArray){
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_Camera->GetViewProjectionMatrix());
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
