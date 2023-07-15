#include <platforms/opengl/OpenGLRendererAPI.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	OpenGLRendererAPI::OpenGLRendererAPI(){
		
	}
	
	OpenGLRendererAPI::~OpenGLRendererAPI(){
		
	}
	
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color){
		glClearColor(color.x, color.y, color.z, color.w);
	}
	
	void OpenGLRendererAPI::Clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexArray){
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetSize(), GL_UNSIGNED_INT, nullptr);
	}
}
