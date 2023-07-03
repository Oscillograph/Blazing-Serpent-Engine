//#include <Window.h>
#include "./WindowsWindow.h"

#include "./systems/events/AppEvent.h"
#include "./systems/events/KeyEvent.h"
#include "./systems/events/MouseEvent.h"

namespace BSE {
	// a global variable in BSE namespace
	bool s_GLFWInitialized = false;
	
	void GLFWErrorCallback(int error, const char* text){
		BSE_CORE_ERROR("GLFW Error {0}: {1}", error, text);
	}
	
	Window* Window::Create(WindowProperties& properties){
		BSE_CORE_TRACE("Calling a Windows platform window creation function");
		return new WindowsWindow(properties);
	}
	
	WindowsWindow::WindowsWindow(const WindowProperties& properties){
		Init(properties);
	}
	
	WindowsWindow::~WindowsWindow(){
		BSE_CORE_TRACE("Window shutdown.");
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
			glfwSetErrorCallback(GLFWErrorCallback);
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
		
		// int version = gladLoadGL((GLADloadproc)glfwGetProcAddress);
		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BSE_CORE_ASSERT(version, "Failed to initialize Glad");
		//BSE_CORE_INFO("Glad initialized: {0}.{1}", GLFW_VERSION_MAJOR(version), GLFW_VERSION_MINOR(version));
		BSE_CORE_INFO("Glad initialized: {0}", version);
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		BSE_CORE_INFO("GLFW user pointer attached to the window.");
		
		SetVSync(true);
		
		BSE_CORE_INFO("VSync set");
		
		// set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});
		
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			switch(action){
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1); // TODO: counter instead of 1 repeats
					data.EventCallback(event); // TODO: DRY!!!111111111111
					break;
				}
			}
		});
		
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			
			KeyTypedEvent event(key);
			data.EventCallback(event);
		});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			switch(action){
				case GLFW_PRESS:{
					MouseButtonPressed event(button, 0); // TODO: decide for repeats
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:{
					MouseButtonReleased event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});
		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});
	}
	
	void WindowsWindow::Shutdown(){
		glfwDestroyWindow(m_Window);
		//gladLoaderUnloadGL();
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
