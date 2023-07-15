#ifndef BSE_VERTEXARRAY_H
#define BSE_VERTEXARRAY_H

#include <Core.h>
#include <renderer/Buffer.h>

namespace BSE {
	class BSE_API VertexArray {
	public:
		virtual ~VertexArray() {}
		
		//virtual void SetData();
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;
		
		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const = 0;
		virtual const IndexBuffer* GetIndexBuffer() const = 0;
		
		static VertexArray* Create();
	};
}

#endif
