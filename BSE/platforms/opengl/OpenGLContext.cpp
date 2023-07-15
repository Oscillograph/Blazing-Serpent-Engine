#include <platforms/opengl/OpenGLContext.h>

namespace BSE {
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{}
	
	void OpenGLContext::Init(){
		BSE_CORE_INFO("GLFW window created.");
		
		glfwMakeContextCurrent(m_Window);
		
		BSE_CORE_INFO("GLFW window context set.");
		
		// int version = gladLoadGL((GLADloadproc)glfwGetProcAddress);
		int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BSE_CORE_ASSERT(version, "Failed to initialize Glad");
		//BSE_CORE_INFO("Glad initialized: {0}.{1}", GLFW_VERSION_MAJOR(version), GLFW_VERSION_MINOR(version));
		BSE_CORE_INFO("Glad initialized: {0}", version);
		
		BSE_CORE_INFO("OpenGL Info.");
		BSE_CORE_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		BSE_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		BSE_CORE_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers(){
		glfwSwapBuffers(m_Window);
	}
}
