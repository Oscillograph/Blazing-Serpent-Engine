#ifndef BSE_SCENE_H
#define BSE_SCENE_H

#include <Core.h>
#include <vendor/entt/entt.hpp>
// #include <systems/ecs/Entity.h>
// #include <systems/ecs/Components.h>

namespace BSE {
	class Entity;
	
	class BSE_API Scene {
	public:
		Scene();
		~Scene();
		
		void OnUpdate(float sceneTime);
		Entity* CreateEntity(const std::string& name = "");
		inline entt::registry& Registry() { return m_Registry; };
	protected:
		
	private:
		entt::registry m_Registry;
	};
}

#endif
