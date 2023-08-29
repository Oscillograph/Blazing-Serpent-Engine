#include <systems/scene/SceneSerializer.h>

namespace BSE {
	SceneSerializer::SceneSerializer(Scene* scene){
		m_SceneContext = scene;
	}
	SceneSerializer::~SceneSerializer(){
		m_SceneContext = nullptr;
	}
	
	bool SceneSerializer::Serialize(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::SerializeToFile(const std::string& filename){
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Unnamed";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_SceneContext->Registry().each([&](auto entityID){
			Entity entity = {entityID, m_SceneContext};
			if (!entity)
				return;
			SerializeEntity(out, entity);
		});
		
		out << YAML::EndSeq;
		out << YAML::EndMap;
		
		return FileIO::WriteRawText(filename, out.c_str());
	}
	
	bool SceneSerializer::SerializeRuntime(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::Deserialize(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::DeserializeFromFile(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::DeserializeRuntime(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity& entity){
		out << YAML::BeginMap;
		out << YAML::Key << "Entity";
		
		char entityID[64];
		sprintf(entityID, "%d", (uint32_t)entity.GetID());
		
		out << YAML::Value << entityID;
		out << YAML::EndMap;
		
		if (entity.HasComponent<NameComponent>()){
			out << YAML::Key << "NameComponent";
			out << YAML::BeginMap;
			
			auto& name = entity.GetComponent<NameComponent>().Name;
			out << YAML::Key << "Name" << YAML::Value << name;
			
			out << YAML::EndMap;
		}
		return false;
	}
}
