#include "Renderer2D.h"

namespace BSE {
	struct Renderer2DStorage {
		VertexArray* QuadVertexArray = nullptr;
		Shader* FlatColorShader = nullptr;
	};
	static Renderer2DStorage* RendererData;
	
	void Renderer2D::Init(){
		RendererData = new Renderer2DStorage;
		
		// Square Vertex Array
		RendererData->QuadVertexArray = VertexArray::Create();
		float squareVertices[3 * 4] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// two numbers for texture coords
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f
		};
		BSE_TRACE("Square Vertices defined");
		
		VertexBuffer* m_SquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));	
		
		m_SquareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			//{BSE::ShaderDataType::Float2, "a_TextureCoordinates"},
		});
		RendererData->QuadVertexArray->AddVertexBuffer(m_SquareVB);
		BSE_TRACE("Square Vertex buffer layout construction successful");
		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		RendererData->QuadVertexArray->SetIndexBuffer(IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
		BSE_TRACE("Square Index buffer bind successful");
		
		// Flat Color Shader
		RendererData->FlatColorShader = Shader::Create("Flat Color", "./shaders/glsl/FlatColor.glsl");
	}
	
	void Renderer2D::Shutdown(){
		delete RendererData;
	}
	
	void Renderer2D::BeginScene(OrthographicCamera* camera){
		RendererData->FlatColorShader->Bind();
		RendererData->FlatColorShader->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
	}
	
	void Renderer2D::EndScene(){
		
	} 
	
	// ----------------------------------------------------------------
	//				2D Specific stuff
	// ----------------------------------------------------------------
	
	void Renderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}
	
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color){
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3({size.x, size.y, 0.0f}));
		glm::vec3 m_SquareTransform = glm::vec3(0.0f);
		
		glm::vec3 pos(position.x, position.y, position.z);
		pos = pos + m_SquareTransform;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		
		RendererData->FlatColorShader->Bind();
		RendererData->FlatColorShader->UploadUniformVec4("u_Color", color);
		RendererData->FlatColorShader->UploadUniformMat4("u_Transform", transform);
		
		RendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::FillRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		
	}
}
