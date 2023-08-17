#include <systems/ecs/Entity.h>

namespace BSE {
	
	Entity::Entity(entt::entity entityID, Scene* scene)
		: m_EntityID(entityID), m_Scene(scene) 
	{}
	
	Entity::~Entity(){
		m_Scene = nullptr;
	}
	
	/*
	template <typename T>
	bool Entity::HasComponent{
		return m_Scene->Registry().has<T>(m_EntityID);
	}
	*/
}
