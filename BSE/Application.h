#ifndef BSE_APPLICATION_H
#define BSE_APPLICATION_H

#include "./Core.h"
#include "./Window.h"
#include "./systems/events/AppEvent.h"
#include "./LayerStack.h"

#ifdef BSE_PLATFORM_WINDOWS
	#include "./platforms/windows/WindowsWindow.h"
#endif

namespace BSE {
	class BSE_API Application {
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);
		
		void Run();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		Window* m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	
	// to be defined in client app
	Application* CreateApplication();
}

#endif
