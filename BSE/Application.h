#ifndef BSE_APPLICATION_H
#define BSE_APPLICATION_H

#include "./Core.h"
//#include "./systems/events/Event.h"
#include "./Window.h"

#ifdef BSE_PLATFORM_WINDOWS
	#include "./platforms/windows/WindowsWindow.h"
#endif

namespace BSE {
	class BSE_API Application {
	public:
		Application();
		virtual ~Application();
		
		void Run();
	private:
		Window* m_Window;
		bool m_Running = true;
	};
	
	// to be defined in client app
	Application* CreateApplication();
}

#endif
