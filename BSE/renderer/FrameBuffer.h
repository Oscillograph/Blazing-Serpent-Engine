#ifndef BSE_FRAMEBUFFER_H
#define BSE_FRAMEBUFFER_H

#include <Core.h>

namespace BSE {
	struct FrameBufferSpecification {
		uint32_t Width;
		uint32_t Height;
		// FrameBufferFormat Format = . . .
		uint32_t Samples = 1;
		
		
		// true means the framebuffer is to be drawn to screen; 
		// false - framebuffer acts like a texture
		// basically, true is an equivalent to glBindFrameBuffer(0)
		bool SwapChainTarget = false; 
	};
	
	class BSE_API FrameBuffer {
	public:
		// virtual FrameBufferSpecification& GetSpecification() = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		virtual uint32_t GetColorAttachmentID() = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		
		static FrameBuffer* FrameBuffer::Create(const FrameBufferSpecification& spec);
		
	protected:
	};
}

#endif
