#include "./Application.h"

#include "./systems/events/AppEvent.h"
#include "./log.h"

namespace BSE{
	Application::Application(){
		
	}
	
	Application::~Application(){
		
	}
	
	void Application::Run(){
		WindowResizeEvent e(1280, 800);
		BSE_TRACE(e);
		
		while(true){
			//TODO
		}
	}
}
