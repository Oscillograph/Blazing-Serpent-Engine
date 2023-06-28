#include "./Application.h"

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{
	Application::Application(){
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
	}
	
	Application::~Application(){
		
	}
	
	void Application::Run(){
		//WindowResizeEvent e(1280, 720);
		//BSE_TRACE(e);
		BSE_TRACE("Enter Application Run routine");
		while(m_Running){
			//TODO
			//BSE_TRACE("glClearColor");
			glClearColor(1, 1, 0, 1);
			//BSE_TRACE("glClear");
			glClear(GL_COLOR_BUFFER_BIT);
			//BSE_TRACE("mWindow->OnUpdate");
			m_Window->OnUpdate();
		}
	}
}
