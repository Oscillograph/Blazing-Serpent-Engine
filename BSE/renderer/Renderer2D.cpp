#include <renderer/Renderer2D.h>

namespace BSE {
	// -------------------------------------------
	// TODO: Design and implement Particles System
	// -------------------------------------------
	
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoordinates;
		float TextureIndex;
		float TilingFactor;
		// TODO: maskId
	};
	
	struct Renderer2DStorage {
		// for batch rendering
		// TODO: Make MaxQuads and corresponding arrays modifiable in runtime
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
		
		Texture2D* TextureSlots[MaxTextureSlots];
		// std::array<Texture2D*, MaxTextureSlots> TextureSlots;
		uint32_t TextureCount = 1; // 0 is a white texture
		
		// TODO: Make Renderer2D Primitives collection accessible by renderer
		glm::vec4 TriangleVertices[3]; // for triangles
		glm::vec4 QuadVertices[4]; // for rectangles
		glm::vec4 CustomVertices[1000]; // for custom figures, like circles, polygons, monkeys, etc.
	};
	static Renderer2DStorage* RendererData;
	
	struct RendererStatistics {
		bool Collecting   = false; 
		uint32_t Vertices = 0;
		uint32_t Flushes  = 0;
		uint32_t Quads    = 0;
		uint32_t Textures = 0;
		
		void StartCollecting() {
			Collecting = true;
			Reset();
		}
		
		void StopCollecting() {
			Collecting = false;
		}
		
		void Reset() { 
			Vertices   = 0;
			Flushes    = 0;
			Quads      = 0;
			Textures   = 0;
		}
	};
	RendererStatistics* RendererStats;
	
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
			{ShaderDataType::Float,  "a_TextureIndex"},
			{ShaderDataType::Float,  "a_TilingFactor"},
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
		
		RendererData->TextureShader = Shader::Create("Texture", "./shaders/glsl/Texture.glsl");
		// RendererData->TextureShader->UploadUniformInt("u_Texture", 0);
		
		// Set all texture slots to white texture
		for (uint32_t i = 0; i < RendererData->MaxTextureSlots; i++){
			RendererData->TextureSlots[i] = RendererData->WhiteTexture;
		}
		RendererData->TextureSlots[0] = RendererData->WhiteTexture;
		RendererData->TextureCount = 1;
		
		// Set vertices for primitives
		RendererData->TriangleVertices[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		RendererData->TriangleVertices[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		RendererData->TriangleVertices[2] = { 0.0f,  0.5f, 0.0f, 1.0f};
		
		RendererData->QuadVertices[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
		RendererData->QuadVertices[1] = { 0.5f, -0.5f, 0.0f, 1.0f};
		RendererData->QuadVertices[2] = { 0.5f,  0.5f, 0.0f, 1.0f};
		RendererData->QuadVertices[3] = {-0.5f,  0.5f, 0.0f, 1.0f};
	}
	
	void Renderer2D::Clear(const glm::vec4& color){
		RenderCommand::SetClearColor(color);
		RenderCommand::Clear();
	}
	
	void Renderer2D::Shutdown(){
		delete RendererData;
	}
	
	void Renderer2D::BeginScene(GeneralCamera* camera){
		RendererData->TextureShader->Bind();
		// BSE_CORE_INFO("BSE1. Is this the stop point?");
		RendererData->TextureShader->UploadUniformMat4("u_ViewProjection", camera->GetViewProjectionMatrix());
		// BSE_CORE_INFO("BSE2. Is this the stop point?");
		
		int samplers[RendererData->MaxTextureSlots];
		for (uint32_t i = 0; i < RendererData->MaxTextureSlots; i++){
			samplers[i] = i;
			// BSE_INFO("Sampler #{0}", i);
		}
		RendererData->TextureShader->UploadUniformIntArray("u_Textures", samplers, RendererData->MaxTextureSlots);
		
		ResetVertexBufferPointer();
		RendererData->TextureCount = 1;
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
		
		RendererData->TextureCount = 1;
	}
	
	void Renderer2D::Flush(){
		for (uint32_t i = 0; i < RendererData->MaxTextureSlots; i++){
			if (RendererData->TextureSlots[i] != nullptr){
				RendererData->TextureSlots[i]->Bind(i);
				// BSE_INFO("TextureSlots {0}:", i);
				// BSE_INFO("{:p}", fmt::ptr(RendererData->TextureSlots[i]));
			} else {
				break;
			}
		}
		
		// BSE_INFO("TextureCount: {0}", RendererData->TextureCount);
		
		if (RendererData->QuadIndexCount > 0){
			// RendererData->QuadVertexArray->Bind();
			RenderCommand::DrawIndexed(RendererData->QuadVertexArray, RendererData->QuadIndexCount);
			// BSE_INFO("TextureIndex: {0}", RendererData->QuadVertexBufferPointer->TextureIndex);
		}
		
		/*
		for (uint32_t i = 0; i < RendererData->TextureCount; i++){
			RendererData->TextureSlots[i]->Unbind(i);
		}
		*/
	}
	
	void Renderer2D::CheckFlush(){
		if ((RendererData->QuadIndexCount >= RendererData->MaxIndices) ||
			(RendererData->TextureCount == RendererData->MaxTextureSlots)) {
			PrepareVertexBuffer();
			Flush();
			ResetVertexBufferPointer();
		}
	}
	
	// ----------------------------------------------------------------
	//				2D Specific stuff
	// ----------------------------------------------------------------
	
	void Renderer2D::DrawFilledRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		// DrawFilledQuad({position.x, position.y, 0.0f}, size, color);
		DrawQuadGeneral({position.x, position.y, 0.0f}, size, 0.0f, nullptr, 1.0f, color, nullptr);
		CheckFlush();
	}
	
	void Renderer2D::DrawTextureRect(const glm::vec2& position, const glm::vec2& size, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		// DrawTextureQuad({position.x, position.y, 0.0f}, size, texture, tilingFactor, tintColor);
		DrawQuadGeneral({position.x, position.y, 0.0f}, size, 0.0f, texture, tilingFactor, tintColor, nullptr);
		CheckFlush();
	}
	
	void Renderer2D::DrawFilledRectRotated(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color){
		// DrawFilledQuadRotated({position.x, position.y, 0.0f}, size, rotation, color);
		DrawQuadGeneral({position.x, position.y, 0.0f}, size, rotation, nullptr, 1.0f, color, nullptr);
		CheckFlush();
	}
	
	void Renderer2D::DrawTextureRectRotated(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor){
		// DrawTextureQuadRotated({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor);
		DrawQuadGeneral({position.x, position.y, 0.0f}, size, rotation, texture, tilingFactor, tintColor, nullptr);
		CheckFlush();
	}
	
	void Renderer2D::DrawSprite(const glm::vec2& position, const glm::vec2& size, float rotation, Texture2DSprite* sprite, float tilingFactor, const glm::vec4& tintColor){
		DrawQuadGeneral({position.x, position.y, 0.0f}, size, rotation, sprite->GetSpriteSheet(), tilingFactor, tintColor, sprite->GetCoordinates());
	}
	void Renderer2D::DrawQuadGeneral(const glm::vec3& position, const glm::vec2& size, float rotation, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor, glm::vec2* spriteCoordinates){
		// default is the 0-th texture which basically a single color background
		float textureIndex = 0.0;
		glm::vec2 textureCoordinates[4];
		textureCoordinates[0] = { 0.0f , 0.0f };
		textureCoordinates[1] = { 1.0f , 0.0f };
		textureCoordinates[2] = { 1.0f , 1.0f };
		textureCoordinates[3] = { 0.0f , 1.0f };
		
		if (texture != nullptr) {
			// check if texture is registered in TextureSlots
			for (uint32_t i = 1; i < RendererData->TextureCount; i++){
				if (RendererData->TextureSlots[i] != nullptr) {
					if (RendererData->TextureSlots[i]->GetID() == texture->GetID()) { // if textures are the same
						textureIndex = (float)i;
						break;
					}
				} else {
					break;
				}
			}
			
			// register the texture if it's not yet
			if (textureIndex == 0.0) {
				textureIndex = (float)(RendererData->TextureCount);
				RendererData->TextureSlots[RendererData->TextureCount] = texture;
				RendererData->TextureCount++;
			}
			
			if (spriteCoordinates != nullptr) {
				textureCoordinates[0] = spriteCoordinates[0];
				textureCoordinates[1] = spriteCoordinates[1];
				textureCoordinates[2] = spriteCoordinates[2];
				textureCoordinates[3] = spriteCoordinates[3];
			}
		}
		
		glm::mat4 transform = OneMat4;
		glm::vec3 pos[4];
		
		if (rotation == 0.0f){
			pos[0] = {position.x, 			position.y, 			position.z};
			pos[1] = {position.x + size.x, 	position.y, 			position.z};
			pos[2] = {position.x + size.x, 	position.y + size.y, 	position.z};
			pos[3] = {position.x, 			position.y + size.y, 	position.z};
		} else {
			transform = 
				glm::translate(OneMat4, position) *
				glm::rotate(OneMat4, glm::radians(rotation), glm::vec3({0.0f, 0.0f, 1.0f})) *
				glm::scale(OneMat4, {size.x, size.y, 1.0f});
		
			for (int i = 0; i < 4; i++){
				pos[i] = glm::vec3(transform * RendererData->QuadVertices[i]);
			}
		}
		
		for (int i = 0; i < 4; i++){
			RendererData->QuadVertexBufferPointer->Position = pos[i];
			RendererData->QuadVertexBufferPointer->Color = tintColor;
			RendererData->QuadVertexBufferPointer->TextureCoordinates = textureCoordinates[i];
			RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
			RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
			RendererData->QuadVertexBufferPointer++;
		}
		
		RendererData->QuadIndexCount += 6;
	}
	
	void Renderer2D::DrawQuadGeneral(const glm::mat4& transform, Texture2D* texture, float tilingFactor, const glm::vec4& tintColor, glm::vec2* spriteCoordinates){
		// default is the 0-th texture which basically a single color background
		float textureIndex = 0.0;
		glm::vec2 textureCoordinates[4];
		textureCoordinates[0] = { 0.0f , 0.0f };
		textureCoordinates[1] = { 1.0f , 0.0f };
		textureCoordinates[2] = { 1.0f , 1.0f };
		textureCoordinates[3] = { 0.0f , 1.0f };
		
		if (texture != nullptr) {
			// check if texture is registered in TextureSlots
			for (uint32_t i = 1; i < RendererData->TextureCount; i++){
				if (RendererData->TextureSlots[i] != nullptr) {
					if (RendererData->TextureSlots[i]->GetID() == texture->GetID()) { // if textures are the same
						textureIndex = (float)i;
						break;
					}
				} else {
					break;
				}
			}
			
			// register the texture if it's not yet
			if (textureIndex == 0.0) {
				textureIndex = (float)(RendererData->TextureCount);
				RendererData->TextureSlots[RendererData->TextureCount] = texture;
				RendererData->TextureCount++;
			}
			
			if (spriteCoordinates != nullptr) {
				textureCoordinates[0] = spriteCoordinates[0];
				textureCoordinates[1] = spriteCoordinates[1];
				textureCoordinates[2] = spriteCoordinates[2];
				textureCoordinates[3] = spriteCoordinates[3];
			}
		}
		
		for (int i = 0; i < 4; i++){
			RendererData->QuadVertexBufferPointer->Position = glm::vec3(transform * RendererData->QuadVertices[i]);
			RendererData->QuadVertexBufferPointer->Color = tintColor;
			RendererData->QuadVertexBufferPointer->TextureCoordinates = textureCoordinates[i];
			RendererData->QuadVertexBufferPointer->TextureIndex = textureIndex;
			RendererData->QuadVertexBufferPointer->TilingFactor = tilingFactor;
			RendererData->QuadVertexBufferPointer++;
		}
		
		RendererData->QuadIndexCount += 6;
	}
	
	void Renderer2D::DrawRect(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
		
	}
}
