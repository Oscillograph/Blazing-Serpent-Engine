#ifndef BSE_OPENGLVERTEXARRAY_H
#define BSE_OPENGLVERTEXARRAY_H

#include <Core.h>
#include <renderer/VertexArray.h>

namespace BSE {
	class BSE_API OpenGLVertexArray : public VertexArray{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		
		//virtual void SetData();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		
		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;
		
		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; };
		
	protected:
		uint32_t m_RendererId;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};
}

#endif
