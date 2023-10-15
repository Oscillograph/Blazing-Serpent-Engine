#include <platforms/opengl/OpenGLRendererAPI.h>
#include <Glad/include/glad/glad.h>

namespace BSE {
	OpenGLRendererAPI::OpenGLRendererAPI(){
		
	}
	
	OpenGLRendererAPI::~OpenGLRendererAPI(){
		
	}
	
	void OpenGLRendererAPI::Init(){
		glEnable(GL_BLEND);
		//glEnable(GL_SCISSOR_TEST);
		//BSE_CORE_TRACE("OpenGL: Enabled Blend");
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//BSE_CORE_TRACE("OpenGL: Set Blend function to (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)");
	}
	
	void OpenGLRendererAPI::Shutdown(){
		
	}
	
	void OpenGLRendererAPI::SetViewPort(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
		glViewport(x, y, w, h);
		//if (glIsEnabled(GL_SCISSOR_TEST)){
		//	glScissor(x, y, w, h);
		//}
	}
	
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color){
		glClearColor(color.x, color.y, color.z, color.w);
	}
	
	void OpenGLRendererAPI::Clear(){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void OpenGLRendererAPI::DrawIndexed(const VertexArray* vertexArray, uint32_t indexCount){
		vertexArray->Bind();
		uint32_t count = (indexCount == 0) ? vertexArray->GetIndexBuffer()->GetSize() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
	
	void OpenGLRendererAPI::DrawLines(const VertexArray* vertexArray, uint32_t vertexCount){
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
	
	void OpenGLRendererAPI::SetLineThickness(float thickness){
		glLineWidth(thickness);
	}
}
