#include "Renderer2D.h"

namespace BSE {
	struct Renderer2DStorage {
		VertexArray* QuadVertexArray = nullptr;
		//Shader* FlatColorShader = nullptr;
		Shader* TextureShader = nullptr;
		
		Texture2D* WhiteTexture;
	};
	static Renderer2DStorage* RendererData;
	
	void Renderer2D::Init(){
		RendererData = new Renderer2DStorage;
		
		// Square Vertex Array
		RendererData->QuadVertexArray = VertexArray::Create();
		float squareVertices[5 * 4] = {
			// one vertice, three-component vector X,Y,Z clipping -1...1
			// two numbers for texture coords
			-0.5f, -0.5f,  0.0f, 	0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f, 	1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f, 	1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f, 	0.0f, 1.0f
		};
		BSE_TRACE("Square Vertices defined");
		
		VertexBuffer* m_SquareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));	
		
		m_SquareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{BSE::ShaderDataType::Float2, "a_TextureCoordinates"},
		});
		RendererData->QuadVertexArray->AddVertexBuffer(m_SquareVB);
		BSE_TRACE("Square Vertex buffer layout construction successful");
		
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		RendererData->QuadVertexArray->SetIndexBuffer(IndexBuffer::Create(squareIndices, (sizeof(squareIndices) / sizeof(uint32_t))));
		BSE_TRACE("Square Index buffer bind successful");
		
		// Flat Color Shader
		// RendererData->FlatColorShader = Shader::Create("Flat Color", "./shaders/glsl/FlatColor.glsl");
		
		// Texture Shader
		RendererData->TextureShader = Shader::Create("Texture", "./shaders/glsl/Texture.glsl");
		RendererData->TextureShader->UploadUniformInt("u_Texture", 0);
		
		RendererData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		RendererData->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
	}
	
	void Renderer2D::Shutdown(){
		delete RendererData;
	}
	
	void Renderer2D::BeginScene(OrthographicCamera* camera){
		//RendererData->FlatColorShader->Bind();
		//RendererData->FlatColorShader->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
		
		RendererData->TextureShader->Bind();
		RendererData->TextureShader->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
	}
	
	void Renderer2D::EndScene(){
		
	} 
	
	// ----------------------------------------------------------------
	//				2D Specific stuff
	// ----------------------------------------------------------------
	
	void Renderer2D::DrawFilledRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		DrawFilledQuad({position.x, position.y, 0.0f}, size, color);
	}
	
	void Renderer2D::DrawFilledQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color){
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3({size.x, size.y, 0.0f}));
		glm::vec3 m_SquareTransform = glm::vec3(0.0f);
		
		glm::vec3 pos(position.x, position.y, position.z);
		pos = pos + m_SquareTransform;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		
		//RendererData->FlatColorShader->Bind();
		RendererData->TextureShader->UploadUniformVec4("u_Color", color);
		RendererData->WhiteTexture->Bind(); // bind white texture
		RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		
		RendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawTextureRect(const glm::vec2& position, const glm::vec2& size, Texture2D* texture){
		DrawTextureQuad({position.x, position.y, 0.0f}, size, texture);
	}
	
	void Renderer2D::DrawTextureQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture){
		RendererData->TextureShader->UploadUniformVec4("u_Color", glm::vec4({1.0f, 1.0f, 1.0f, 1.0f}));
		
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3({size.x, size.y, 0.0f}));
		glm::vec3 m_SquareTransform = glm::vec3(0.0f);
		
		glm::vec3 pos(position.x, position.y, position.z);
		pos = pos + m_SquareTransform;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
		
		// RendererData->TextureShader->Bind();
		// RendererData->TextureShader->UploadUniformVec4("u_Color", color);
		RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		
		texture->Bind();
		
		RendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		
	}
}
