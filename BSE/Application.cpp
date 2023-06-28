#include "./Application.h"

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{

	#define BIND_EVENT_FUNCTION(x) std::bind(Application::x, this, std::placeholders::_1) 
	
	Application::Application(){
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
		// TODO: callback doesn't set and brings app crash with 0xc000005 error.
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
		// m_Window->SetEventCallback(std::bind(&(Application::OnEvent), this, std::placeholders::_1));
		// m_Window->SetEventCallback(&(Application::OnEvent));
		BSE_TRACE("OnEvent callback bind successful");
	}
	
	Application::~Application(){
		
	}
	
	void Application::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
		
		BSE_INFO("{0}", e);
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
	
	// Events
	
	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}
}
