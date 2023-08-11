#ifndef BSE_OPENGLFRAMEBUFFER_H
#define BSE_OPENGLFRAMEBUFFER_H

#include <Core.h>
#include <renderer/FrameBuffer.h>

namespace BSE {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		
		void Invalidate();

		virtual uint32_t GetColorAttachmentID() override { return m_ColorAttachment; };
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };
		
		virtual void Bind() override;
		virtual void Unbind() override;
		
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FrameBufferSpecification m_Specification;
	};
}

#endif
