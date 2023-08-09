#ifndef BSE_TEXTURE_H
#define BSE_TEXTURE_H

#include <Core.h>

namespace BSE {
	class BSE_API Texture {
	public:	
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetID() const = 0;
		// virtual uint32_t GetFormat() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void Unbind(uint32_t slot = 0) const = 0;
		
		virtual bool operator==(const Texture* other) const = 0;
	};
	
	
	class BSE_API Texture2D : public Texture {
	public:
		static Texture2D* Create(uint32_t width, uint32_t height);
		static Texture2D* Create(std::string path);
	};
}

#endif
