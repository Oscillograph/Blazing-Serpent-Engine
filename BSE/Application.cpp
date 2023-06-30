#include "./Application.h"

//#include "./systems/events/AppEvent.h"
//#include "./log.h"

namespace BSE{

	// DONE: figure out how to do it with lambda functions
	// #define BIND_EVENT_FUNCTION(x) std::bind(Application::x, this, std::placeholders::_1)
	// No need for this macros anymore
	
	Application::Application(){
		BSE_TRACE("Trying to create an app window");
		m_Window = Window::Create(*(new WindowProperties()));
		BSE_TRACE("Window created and stored in m_Window");
		
		m_Window->SetEventCallback([this](Event& event){
			OnEvent(event);
		});
		
		BSE_TRACE("OnEvent callback bind successful");
	}
	
	Application::~Application(){
		
	}
	
	void Application::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event){
			return OnWindowClose(event);
		});
		
		BSE_INFO("{0}", e);
	}
	
	void Application::Run(){
		BSE_TRACE("Enter Application Run routine");
		while(m_Running){
			//BSE_TRACE("glClearColor");
			glClearColor(0.3, 0.3, 0.5, 1);
			//BSE_TRACE("glClear");
			glClear(GL_COLOR_BUFFER_BIT);
			//BSE_TRACE("mWindow->OnUpdate");
			m_Window->OnUpdate();
		}
	}
	
	// ------------------------------------
	// Events
	
	bool Application::OnWindowClose(WindowCloseEvent& e){
		m_Running = false;
		return true;
	}
}
