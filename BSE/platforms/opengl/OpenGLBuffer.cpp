#include <platforms/opengl/OpenGLBuffer.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	// ----------------------------------------------------------------------
	// 								Vertex Buffer
	// ----------------------------------------------------------------------
	
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size){
		// Vertex array
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);
		
		// The app crashed here when i used glCreateBuffers (OpenGL 4.5+) instead of glGenBuffers (can work on my videocard)
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		
		// Vertex buffer
		//glGenBuffers(1, &m_VertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer(){
		glDeleteBuffers(1, &m_RendererId);
	}
	
	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}
	
	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	// ----------------------------------------------------------------------
	// 								Index Buffer
	// ----------------------------------------------------------------------
	
	
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size)
		: m_Size(size)
	{
		// Vertex array
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);
		
		// The app crashed here when i used glCreateBuffers (OpenGL 4.5+) instead of glGenBuffers (can work on my videocard)
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), indices, GL_STATIC_DRAW);
		
		// Vertex buffer
		//glGenBuffers(1, &m_VertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	}
	
	OpenGLIndexBuffer::~OpenGLIndexBuffer(){
		glDeleteBuffers(1, &m_RendererId);
	}
	
	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}
	
	void OpenGLIndexBuffer::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
