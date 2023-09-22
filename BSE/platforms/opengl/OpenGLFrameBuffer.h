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
		void DeleteEverything();
		virtual void Resize(const glm::vec2& size) override;
		
		virtual uint32_t GetWidth() override { return m_Specification.Width; };
		virtual uint32_t GetHeight() override { return m_Specification.Height; };
		
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual uint32_t GetColorAttachmentID(uint32_t index = 0) override { return m_ColorAttachments[index]; };
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };
		
		virtual void Bind() override;
		virtual void Unbind() override;
		
	private:
		uint32_t m_RendererID;
		// uint32_t m_ColorAttachment;
		// uint32_t m_DepthAttachment;
		FrameBufferSpecification m_Specification;
		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecifications;
		FrameBufferTextureSpecification m_DepthAttachmentSpecification;
		
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment;
	};
}

#endif
