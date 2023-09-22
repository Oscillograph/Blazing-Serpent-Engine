#ifndef BSE_FRAMEBUFFER_H
#define BSE_FRAMEBUFFER_H

#include <Core.h>

namespace BSE {
	enum class FrameBufferTextureFormat {
		None = 0,
		
		// Color
		RGBA8,
		RED_INTEGER,
		
		// Depth / stencil
		DEPTH24STENCIL8,
		
		// Defaults
		Depth = DEPTH24STENCIL8
	};
	
	struct FrameBufferTextureSpecification {
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format)
			: TextureFormat(format) {}
		
		FrameBufferTextureFormat TextureFormat = FrameBufferTextureFormat::None;
		// TODO: Filtering / Wrap
	};
	
	struct FrameBufferAttachmentSpecification {
		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(std::initializer_list<FrameBufferTextureSpecification> attachments)
			: Attachments(attachments) {}
		std::vector<FrameBufferTextureSpecification> Attachments;
	};
	
	struct FrameBufferSpecification {
		uint32_t Width;
		uint32_t Height;
		FrameBufferAttachmentSpecification Attachments;
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
		virtual uint32_t GetColorAttachmentID(uint32_t index = 0) = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(const glm::vec2& size) = 0;
		virtual uint32_t GetWidth() = 0;
		virtual uint32_t GetHeight() = 0;
		
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;
		
		static FrameBuffer* Create(const FrameBufferSpecification& spec);
		
	protected:
	};
}

#endif
