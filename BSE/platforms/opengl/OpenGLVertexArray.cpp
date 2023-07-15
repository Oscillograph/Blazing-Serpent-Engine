#include <platforms/opengl/OpenGLVertexArray.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	static const GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float: 	return GL_FLOAT; break;
			case ShaderDataType::Float2: 	return GL_FLOAT; break;
			case ShaderDataType::Float3: 	return GL_FLOAT; break;
			case ShaderDataType::Float4: 	return GL_FLOAT; break;
			case ShaderDataType::Int: 		return GL_INT; break;
			case ShaderDataType::Int2: 		return GL_INT; break;
			case ShaderDataType::Int3: 		return GL_INT; break;
			case ShaderDataType::Int4: 		return GL_INT; break;
			case ShaderDataType::Mat3: 		return GL_FLOAT_MAT3; break;
			case ShaderDataType::Mat4: 		return GL_FLOAT_MAT4; break;
			case ShaderDataType::Bool: 		return GL_BOOL; break;
		}
		BSE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_NONE;
	}
	
	
	OpenGLVertexArray::OpenGLVertexArray(){
		glGenVertexArrays(1, &m_RendererId);
		// BSE_TRACE("Vertex array generated");
	}
	
	OpenGLVertexArray::~OpenGLVertexArray(){
		glDeleteVertexArrays(1, &m_RendererId);
	}
	
	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererId);
		// BSE_TRACE("Vertex array bound");
	}
	
	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* vertexBuffer) {
		BSE_CORE_ASSERT(vertexBuffer->GetLayout()->GetElements().size(), "Vertex Buffer has no layout");
		
		glBindVertexArray(m_RendererId);
		vertexBuffer->Bind();
		
		uint32_t index = 0;
		auto layout = vertexBuffer->GetLayout();
		for (auto element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			index++;
		}
		
		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* indexBuffer) {
		glBindVertexArray(m_RendererId);
		indexBuffer->Bind();
		
		m_IndexBuffer = indexBuffer;
	}
}


