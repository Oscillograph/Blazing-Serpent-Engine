#ifndef BSE_SHADEREXAMPLE_H
#define BSE_SHADEREXAMPLE_H

#include <Core.h>
#include <platforms/opengl/OpenGLContext.h>
#include <glm/glm.hpp>

namespace BSE {
	class BSE_API ShaderExample {
	public:
		ShaderExample(const std::string& vertexSrc, const std::string fragmentSrc);
		~ShaderExample();
		
		void Bind() const;
		void Unbind() const;
		
		void UploadUniformMat4(std::string name, const glm::mat4& matrix);
		void UploadUniformVec4(std::string name, const glm::vec4& vector);
	protected:
		uint32_t m_RendererId;
	};
}

#endif
