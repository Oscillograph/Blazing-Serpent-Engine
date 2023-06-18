#ifndef BSE_APPLICATION_H
#define BSE_APPLICATION_H

#include "./Core.h"

namespace BSE {
	class BSE_API Application {
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};
	
	// to be defined in client app
	Application* CreateApplication();
}

#endif
