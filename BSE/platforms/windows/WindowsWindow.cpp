//#include <Window.h>
#include "./WindowsWindow.h"

namespace BSE {
	// a global variable in BSE namespace
	bool s_GLFWInitialized = false;
	
	Window* Window::Create(WindowProperties& properties){
		BSE_CORE_TRACE("Calling a Windows platform window creation function");
		return new WindowsWindow(properties);
	}
	
	WindowsWindow::WindowsWindow(const WindowProperties& properties){
		Init(properties);
	}
	
	WindowsWindow::~WindowsWindow(){
		Shutdown();
	}
	
	void WindowsWindow::Init(const WindowProperties& properties){
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;
		m_Data.VSync = true;
		m_Data.EventCallback = Callback_dummy;
		
		BSE_CORE_INFO("Window initialization start {0}, {1}, {2}", properties.Title, properties.Width, properties.Height);
		
		if (!s_GLFWInitialized){
			int success = glfwInit();
			BSE_CORE_ASSERT(success, "Could not initialize GLFW!");
			s_GLFWInitialized = true;
		}
		
		BSE_CORE_INFO("GLFW Initialized {0}", s_GLFWInitialized);
		
		m_Window = glfwCreateWindow((int)properties.Width, 
			(int)properties.Height, m_Data.Title.c_str(), 
			nullptr, 
			nullptr);
		
		BSE_CORE_INFO("GLFW window created.");
		
		glfwMakeContextCurrent(m_Window);
		
		BSE_CORE_INFO("GLFW window context set.");
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		//glfwSetWindowUserPointer(m_Window, nullptr);
		
		BSE_CORE_INFO("GLFW user pointer attached to the window.");
		
		SetVSync(true);
		
		BSE_CORE_INFO("VSync set");
	}
	
	void WindowsWindow::Shutdown(){
		glfwDestroyWindow(m_Window);
	}
	
	void WindowsWindow::OnUpdate() const {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	
	void WindowsWindow::SetVSync(bool enabled){
		if (enabled){
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
		
		m_Data.VSync = enabled;
	}
	
	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}
