#ifndef BSE_SCENESERIALIZER_H
#define BSE_SCENESERIALIZER_H

#include <Core.h>
#include <systems/scene/Scene.h>
#include <systems/ecs/Entity.h>

#include <systems/ecs/Components.h>
#include <systems/OrthographicCameraController.h>

namespace BSE {
	class BSE_API SceneSerializer {
	public:
		SceneSerializer(Scene* scene);
		~SceneSerializer();
		
		bool Serialize(const std::string& filename);
		bool SerializeToFile(const std::string& filename);
		bool SerializeRuntime(const std::string& filename);
		
		bool Deserialize(const std::string& filename);
		bool DeserializeFromFile(const std::string& filename);
		bool DeserializeRuntime(const std::string& filename);
		
		bool SerializeEntity(YAML::Emitter& out, Entity& entity);
	private:
		Scene* m_SceneContext = nullptr;
	};
}

#endif
