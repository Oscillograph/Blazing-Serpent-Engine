#ifndef BSE_OPENGLCONTEXT_H
#define BSE_OPENGLCONTEXT_H

#include <Core.h>
#include <renderer/GraphicsContext.h>
#include <vendor/Glad/include/glad/glad.h>
#include <vendor/glfw/glfw3.h>

// struct GLFWwindow;

namespace BSE {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* window);
		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void CopyBuffers() override;
	protected:
		GLFWwindow* m_Window;
	};
}

#endif
