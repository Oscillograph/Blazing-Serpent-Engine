#include <renderer/Material.h>

namespace BSE {
	template <typename T>
	void MaterialInstance::Set(std::string name, MaterialSetType type, T& value){
		if (type == MaterialSetType::Color){
			m_Material->GetShader()->UploadUniformVec4(name, value);
		}
	}
}

