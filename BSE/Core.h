#ifndef BSE_CORE_H
#define BSE_CORE_H

#include <ProtoCore.h>
#include <log.h>
#include <Misc.h>
#include <utils/FileIO.h>
#include <utils/Time.h>

// basic functions
namespace BSE {
	// BSE_API void print_hello(); 
	
	// BSE_API void Callback_dummy(Event& event);
	struct BSE_Rect {
		float x;
		float y;
		float w;
		float h;
	};
}

#endif
