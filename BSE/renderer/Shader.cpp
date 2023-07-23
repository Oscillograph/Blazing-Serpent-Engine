#include <renderer/RendererAPI.h>
#include <renderer/Shader.h>
#include <platforms/opengl/OpenGLShader.h>

namespace BSE {
	
	// ----------------------------------------------------------------
	//								Shader
	// ----------------------------------------------------------------
	Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc){
		switch (RendererAPI::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			// BSE_CORE_TRACE("OpenGL Shader is being created");
			return new OpenGLShader(name, vertexSrc, fragmentSrc);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	Shader* Shader::Create(const std::string& name, const std::string& filepath){
		switch (RendererAPI::GetAPI()){
		case RendererAPI::API::None:
			BSE_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
			break;
		case RendererAPI::API::OpenGL:
			// BSE_CORE_TRACE("OpenGL Shader is being created");
			return new OpenGLShader(name, filepath);
			break;
		}
		BSE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	
	
	// ----------------------------------------------------------------
	//							Shader Library
	// ----------------------------------------------------------------
	void ShaderLibrary::Add(const std::string& name, Shader* shader){
		BSE_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists in the library");
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(Shader* shader){
		auto& name = shader->GetName();
		BSE_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists in the library");
		m_Shaders[name] = shader;
	}
	
	Shader* ShaderLibrary::Load(const std::string& filepath){
		auto name = FileIO::GetName(filepath);
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return m_Shaders[name];
	}
	
	Shader* ShaderLibrary::Load(const std::string& name, const std::string& filepath){
		auto shader = Shader::Create(name, filepath);
		Add(name, shader);
		return m_Shaders[name];
	}
	
	Shader* ShaderLibrary::Get(const std::string& name){
		if (m_Shaders.find(name) != m_Shaders.end()){
			return m_Shaders[name];
		} else {
			return nullptr;
		}
		BSE_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader doesn't exist in the library");
	}
}
