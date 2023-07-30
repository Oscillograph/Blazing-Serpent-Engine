#ifndef BSE_OPENGLBUFFER_H
#define BSE_OPENGLBUFFER_H

#include <Core.h>
#include <renderer/Buffer.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		
		// virtual void SetData();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		// virtual void SetLayout(BufferLayout& layout) override;
		
		virtual const BufferLayout& GetLayout() override { return m_Layout; };
		virtual bool SetLayout(const BufferLayout& layout) override { m_Layout = layout; return true; }
		virtual void SetData(const void* data, uint32_t size) override;
		
		//static OpenGLVertexBuffer* Create(float* vertices, uint32_t size);
		
	protected:
		uint32_t m_RendererId;
		BufferLayout m_Layout;
	};
	
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		
		// virtual void SetData();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual uint32_t GetSize() const { return m_Count; }
		//static OpenGLIndexBuffer* Create(uint32_t* indices, uint32_t size);
		
	protected:
		uint32_t m_RendererId;
		uint32_t m_Count;
	};
}

#endif
