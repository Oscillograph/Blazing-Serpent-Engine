#ifndef BSE_SCENE_H
#define BSE_SCENE_H

#include <Core.h>
#include <systems/ecs/Entity.h>
#include <systems/ecs/Components.h>

namespace BSE {
	class BSE_API Scene {
	public:
		Scene();
		~Scene();
		
		void OnUpdate(float sceneTime);
		inline entt::entity CreateEntity() { return m_Registry.create(); };
		inline entt::registry& Registry() { return m_Registry; };
	protected:
		
	private:
		entt::registry m_Registry;
	};
}

#endif
