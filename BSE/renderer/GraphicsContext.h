#ifndef BSE_GRAPHICSCONTEXT_H
#define BSE_GRAPHICSCONTEXT_H

#include <Core.h>

namespace BSE {
	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void CopyBuffers() = 0;
	};	
}

#endif
