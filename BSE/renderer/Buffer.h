#ifndef BSE_BUFFER_H
#define BSE_BUFFER_H

#include <Core.h>

namespace BSE {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};
	
	static uint32_t ShaderDataTypeSize(ShaderDataType type){
		switch (type) {
			case ShaderDataType::Float:		return 4; break;
			case ShaderDataType::Float2: 	return 4 * 2; break;
			case ShaderDataType::Float3: 	return 4 * 3; break;
			case ShaderDataType::Float4: 	return 4 * 4; break;
			case ShaderDataType::Int: 		return 4; break;
			case ShaderDataType::Int2: 		return 4 * 2; break;
			case ShaderDataType::Int3: 		return 4 * 3; break;
			case ShaderDataType::Int4: 		return 4 * 4; break;
			case ShaderDataType::Mat3: 		return 4 * 3 * 3; break;
			case ShaderDataType::Mat4: 		return 4 * 4 * 4; break;
			case ShaderDataType::Bool: 		return 1; break;
		}
		BSE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}
	
	struct BSE_API BufferElement {
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;
		//uint32_t Count;
		
		BufferElement(){}
		
		BufferElement(ShaderDataType type, std::string name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) 
		{
			
		}
		
		const uint32_t GetComponentCount(){
			switch(Type){
				case ShaderDataType::Float: 	return 1; break;
				case ShaderDataType::Float2: 	return 2; break;
				case ShaderDataType::Float3: 	return 3; break;
				case ShaderDataType::Float4: 	return 4; break;
				case ShaderDataType::Int: 		return 1; break;
				case ShaderDataType::Int2: 		return 2; break;
				case ShaderDataType::Int3: 		return 3; break;
				case ShaderDataType::Int4: 		return 4; break;
				case ShaderDataType::Mat3: 		return 3 * 3; break;
				case ShaderDataType::Mat4: 		return 4 * 4; break;
				case ShaderDataType::Bool: 		return 1; break;
			}
			BSE_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};
	
	class BSE_API BufferLayout {
	public:
		BufferLayout(){}
		
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}
		
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline const uint32_t GetStride() const { return m_Stride; }
		
		const std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		const std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		
	private:
		void CalculateOffsetAndStride(){
			m_Stride = 0;
			for (auto& element : m_Elements){
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
		
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0; // stride to calculate offsets between layouts
	};
	
	class BSE_API VertexBuffer {
	public:
		virtual ~VertexBuffer() {}
		
		//virtual void SetData();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual const BufferLayout& GetLayout() = 0;
		virtual bool SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;
		
		static VertexBuffer* Create(uint32_t size);
		static VertexBuffer* Create(float* vertices, uint32_t size);
	protected:
		
	};
	
	// currently BSE supports only 32-bit buffers
	class BSE_API IndexBuffer {
	public:
		virtual ~IndexBuffer() {}
		
		//virtual void SetData();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual uint32_t GetSize() const = 0;
		
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	protected:
		
	};
}

#endif
