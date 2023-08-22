#ifndef BSE_ENTITY_H
#define BSE_ENTITY_H

#include <Core.h>
#include <systems/scene/Scene.h>
#include <vendor/entt/entt.hpp>

namespace BSE {
	class BSE_API Entity {
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(entt::entity entityID, Scene* scene);
		~Entity();
		
		inline entt::entity GetID(){ return m_EntityID; } 
		
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args){
			// BSE_ASSERT(!HasComponent<T>(), "Entity already has the component.");
			return m_Scene->Registry().emplace<T>(this->m_EntityID, std::forward<Args>(args)...);
		}
		
		template <typename T>
		T& GetComponent(){
			// BSE_ASSERT(HasComponent<T>(), "Entity doesn't have the component.");
			return m_Scene->Registry().get<T>(this->m_EntityID);
		}
		
		template <typename T>
		bool HasComponent(){
			return m_Scene->Registry().all_of<T>(this->m_EntityID);
		}
		
		template <typename T>
		void RemoveComponent(){
			// BSE_ASSERT(HasComponent<T>(), "Entity doesn't have the component.");
			return m_Scene->Registry().erase<T>(this->m_EntityID);
		}
		
		operator bool() { return (this->m_EntityID != entt::null); }
	private:
		entt::entity m_EntityID;
		Scene* m_Scene;
	};
}

#endif
