#include "Renderer2D.h"

namespace BSE {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoordinates;
		float TextureIndex;
		float TilingFactor;
		// TODO: textureId, maskId
	};
	
	struct Renderer2DStorage {
		// for batch rendering
		const uint32_t MaxQuads = 36000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: caps by renderer capabilities
		
		uint32_t QuadIndexCount = 0;
		
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPointer = nullptr;
		// --------------------------------------
		
		VertexArray* QuadVertexArray = nullptr;
		VertexBuffer* QuadVertexBuffer = nullptr;
		Shader* TextureShader = nullptr;
		Texture2D* WhiteTexture;
		
		// Texture2D* TextureSlot[MaxTextureSlots];
		std::array<Texture2D*, MaxTextureSlots> TextureSlot;
		uint32_t TextureSlotIndex = 1; // 0 is a white texture
	};
	static Renderer2DStorage* RendererData;
	
	void Renderer2D::Init(){
		RendererData = new Renderer2DStorage;
		
		// Square Vertex Array
		RendererData->QuadVertexArray = VertexArray::Create();
		BSE_TRACE("Square Vertices created");
		
		RendererData->QuadVertexBuffer = VertexBuffer::Create(RendererData->MaxVertices * sizeof(QuadVertex));	
		
		RendererData->QuadVertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TextureCoordinates"},
			{ShaderDataType::Float, "a_TextureIndex"},
			{ShaderDataType::Float, "a_TilingFactor"},
		});
		RendererData->QuadVertexArray->AddVertexBuffer(RendererData->QuadVertexBuffer);
		BSE_TRACE("Square Vertex buffer layout construction successful");
		
		RendererData->QuadVertexBufferBase = new QuadVertex[RendererData->MaxVertices];
		
		uint32_t* quadIndices = new uint32_t[RendererData->MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < RendererData->MaxIndices; i += 6 ){
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		IndexBuffer* quadIB = IndexBuffer::Create(quadIndices, RendererData->MaxIndices);
		RendererData->QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		BSE_TRACE("Square Index buffer bind successful");
		
		
		// White color texture
		RendererData->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xff99ffff;
		RendererData->WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
		
		// Texture Shader
		int samplers[RendererData->MaxTextureSlots];
		for (uint32_t i = 0; i < RendererData->MaxTextureSlots; i++){
			samplers[i] = i;
		}
		
		RendererData->TextureShader = Shader::Create("Texture", "./shaders/glsl/Texture.glsl");
		// RendererData->TextureShader->UploadUniformInt("u_Texture", 0);
		RendererData->TextureShader->UploadUniformIntArray("u_Textures", samplers, RendererData->MaxTextureSlots);
		
		// set all texture slots to 0
		RendererData->TextureSlot[0] = RendererData->WhiteTexture;
	}
	
	void Renderer2D::Clear(const glm::vec4& color){
		RenderCommand::SetClearColor(color);
		RenderCommand::Clear();
	}
	
	void Renderer2D::Shutdown(){
		delete RendererData;
	}
	
	void Renderer2D::BeginScene(OrthographicCamera* camera){
		RendererData->TextureShader->Bind();
		RendererData->TextureShader->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
		
		ResetVertexBufferPointer();
		// RendererData->TextureSlotIndex = 1;
	}
	
	void Renderer2D::EndScene(){
		PrepareVertexBuffer();
		Flush();
	} 
	
	void Renderer2D::PrepareVertexBuffer(){
		// why uint8_t on the right, while uint32_t on the left?
		uint32_t dataSize = (uint8_t*)RendererData->QuadVertexBufferPointer - (uint8_t*)RendererData->QuadVertexBufferBase;  
		RendererData->QuadVertexBuffer->SetData(RendererData->QuadVertexBufferBase, dataSize);
	}
	
	void Renderer2D::ResetVertexBufferPointer(){
		RendererData->QuadIndexCount = 0;
		RendererData->QuadVertexBufferPointer = RendererData->QuadVertexBufferBase;
	}
	
	void Renderer2D::Flush(){
		for (uint32_t i = 0; i < RendererData->TextureSlotIndex; i++){
			RendererData->TextureSlot[i]->Bind(i);
			// BSE_INFO("TextureSlot: {:p}", fmt::ptr(RendererData->TextureSlot[i]));
			// BSE_INFO("TextureSlot {0}", i);
		}
		
		// BSE_INFO("TextureSlotIndex: {0}", RendererData->TextureSlotIndex);
		
		if (RendererData->QuadIndexCount > 0){
			RenderCommand::DrawIndexed(RendererData->QuadVertexArray, RendererData->QuadIndexCount);
		}
	}
	
	void Renderer2D::CheckFlush(){
		if (RendererData->QuadIndexCount >= RendererData->MaxIndices) {
			PrepareVertexBuffer();
			Flush();
			ResetVertexBufferPointer();
		}
	}
	
	// ----------------------------------------------------------------
	//				2D Specific stuff
	// ----------------------------------------------------------------
	
	void Renderer2D::DrawFilledRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		DrawFilledQuad({position.x, position.y, 0.0f}, size, color);
		CheckFlush();
	}
	
	void Renderer2D::DrawFilledQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color){
		float textureIndex = 0.0f; // white texture
		float tilingFactor = 1.0f;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x, position.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = color;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {0.0f, 1.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x + size.x, position.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = color;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {1.0f, 1.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x + size.x, position.y + size.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = color;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {1.0f, 0.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x, position.y + size.y, 0.0f};;
		RendererData->QuadVertexBufferPointer->Color = color;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {0.0f, 0.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadIndexCount += 6;
		
		// glm::mat4 transform = glm::translate(OneMat4, glm::vec3(position.x, position.y, position.z))
		//		* glm::scale(OneMat4, glm::vec3({size.x, size.y, 0.0f}));
		
		// float tilingFactor = 1.0f;

		// RendererData->TextureShader->UploadUniformVec4("u_Color", color);
		// RendererData->TextureShader->UploadUniformFloat("u_TilingFactor", tilingFactor);
		// RendererData->WhiteTexture->Bind(); // bind white texture
		// RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		
		// RendererData->QuadVertexArray->Bind();
		// RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawTextureRect(const glm::vec2& position, const glm::vec2& size, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		DrawTextureQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawTextureQuad(const glm::vec3& position, const glm::vec2& size, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < RendererData->TextureSlot.size(); i++){
			if (RendererData->TextureSlot[i] == texture) { // if textures are equal
				textureIndex = (float)i;
				break;
			}
		}
		// BSE_INFO("TextureIndex: {0}", textureIndex);
		
		if (textureIndex == 0.0f) {
			textureIndex = (float)(RendererData->TextureSlotIndex);
			RendererData->TextureSlot[RendererData->TextureSlotIndex] = texture;
			RendererData->TextureSlotIndex++;
		}
		
		textureIndex = 2.0f;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x, position.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = tintColor;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {0.0f, 1.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x + size.x, position.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = tintColor;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {1.0f, 1.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x + size.x, position.y + size.y, 0.0f};
		RendererData->QuadVertexBufferPointer->Color = tintColor;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {1.0f, 0.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadVertexBufferPointer->Position = {position.x, position.y + size.y, 0.0f};;
		RendererData->QuadVertexBufferPointer->Color = tintColor;
		RendererData->QuadVertexBufferPointer->TextureCoordinates = {0.0f, 0.0f};
		RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
		RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
		RendererData->QuadVertexBufferPointer++;
		
		RendererData->QuadIndexCount += 6;
		
		//RendererData->TextureShader->UploadUniformVec4("u_Color", tintColor);
		//glm::mat4 transform = glm::translate(OneMat4, glm::vec3(position.x, position.y, position.z))
		//		* glm::scale(OneMat4, glm::vec3({size.x, size.y, 0.0f}));
		//RendererData->TextureShader->UploadUniformFloat("u_TilingFactor", tilingFactor);
		//RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		//
		//texture->Bind();
		//
		//RendererData->QuadVertexArray->Bind();
		//RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawFilledRectRotated(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color){
		DrawFilledQuadRotated({position.x, position.y, 0.0f}, size, rotation, color);
	}
	
	void Renderer2D::DrawFilledQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color){
		glm::mat4 transform = glm::translate(OneMat4, glm::vec3(position.x, position.y, position.z))
					* glm::rotate(OneMat4, rotation, glm::vec3({0.0f, 0.0f, 1.0f}))
					* glm::scale(OneMat4, glm::vec3({size.x, size.y, 0.0f}));
		
		float tilingFactor = 1.0f;
		
		RendererData->TextureShader->UploadUniformVec4("u_Color", color);
		RendererData->TextureShader->UploadUniformFloat("u_TilingFactor", tilingFactor);
		RendererData->WhiteTexture->Bind(); // bind white texture
		RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		
		RendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawTextureRectRotated(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		DrawTextureQuadRotated({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
	}
	
	void Renderer2D::DrawTextureQuadRotated(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		RendererData->TextureShader->UploadUniformVec4("u_Color", tintColor);
		
		glm::mat4 transform = glm::translate(OneMat4, glm::vec3(position.x, position.y, position.z))
					* glm::rotate(OneMat4, rotation, glm::vec3({0.0f, 0.0f, 1.0f}))
					* glm::scale(OneMat4, glm::vec3({size.x, size.y, 0.0f}));
		
		RendererData->TextureShader->UploadUniformMat4("u_Transform", transform);
		RendererData->TextureShader->UploadUniformFloat("u_TilingFactor", tilingFactor);
		
		texture->Bind();
		
		RendererData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(RendererData->QuadVertexArray);
	}
	
	void Renderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		
	}
}
