#ifndef BSE_OPENGLSHADER_H
#define BSE_OPENGLSHADER_H

#include <Core.h>
#include <renderer/Shader.h>

namespace BSE {
	class BSE_API OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& name, const std::string& filepath);
		virtual ~OpenGLShader();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
		// virtual void UploadUniformBuffer(std::string name, T buffer) override;
		// virtual void UploadUniformBuffer() override
		
		void UploadUniformInt(std::string name, const int& value) const override;
		void UploadUniformIntArray(std::string name, int* values, int count) const override;
		void UploadUniformFloat(std::string name, const float& value) const override;
		
		void UploadUniformVec2(std::string name, const glm::vec2& vector) const override;
		void UploadUniformVec3(std::string name, const glm::vec3& vector) const override;
		void UploadUniformVec4(std::string name, const glm::vec4& vector) const override;
		
		void UploadUniformMat3(std::string name, const glm::mat3& matrix) const override;
		void UploadUniformMat4(std::string name, const glm::mat4& matrix) const override;
		
	
	//protected:
	//	uint32_t m_RendererId;
	private:
		std::unordered_map<GLenum, std::string> Preprocess(std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	};
}

#endif
