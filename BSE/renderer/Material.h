#ifndef BSE_MATERIAL_H
#define BSE_MATERIAL_H

#include <Core.h>
#include <renderer/Shader.h>

namespace BSE {
	enum class MaterialSetType {
		None = 0,
		Color,
		Texture,
	};
	
	class BSE_API MaterialRef {
	public:
		MaterialRef(Shader* shader)
			: m_Shader(shader)
		{}
		~MaterialRef();
		
		inline Shader* GetShader() { return m_Shader; }
		inline void SetShader(Shader* shader) { m_Shader = shader; }
	private:
		Shader* m_Shader = nullptr;
	};
	
	
	class BSE_API MaterialInstance {
	public:
		MaterialInstance(MaterialRef* material)
			: m_Material(material)
		{}
		~MaterialInstance(){
			if (m_Material != nullptr){
				delete m_Material;
			}
		}
		
		template <typename T>
		void Set(std::string name, MaterialSetType type, T& value);
		
		inline void Bind(){ m_Material->GetShader()->Bind(); }
		
		inline MaterialRef* GetMaterial() { return m_Material; }
		inline void SetMaterial(MaterialRef* material) { m_Material = material; }
		
	private:
		MaterialRef* m_Material = nullptr;
	};
}

#endif
