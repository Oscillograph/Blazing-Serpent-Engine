#ifndef BSE_ENTITY_H
#define BSE_ENTITY_H

#include <Core.h>
#include <systems/scene/Scene.h>
#include <systems/scene/UUID.h>
#include <vendor/entt/entt.hpp>

namespace BSE {
	class BSE_API Entity {
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(entt::entity entityID, Scene* scene);
		~Entity();
		
		inline entt::entity GetID(){ return m_EntityID; }
		inline uint64_t GetUUID(){ return m_UUID; }
		inline void SetUUID(uint64_t uuid){ m_UUID = uuid; }
		inline Scene* GetScene(){ return m_Scene; };
		
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
		bool operator==(Entity* other) {
			return ((this->m_EntityID == other->GetID()) && (this->m_Scene == other->GetScene()));
		};
		bool operator!=(Entity* other) {
			return !(this == other);
		};
		bool operator==(Entity& other) {
			return ((m_EntityID == other.GetID()) && (m_Scene == other.GetScene()));
		};
		bool operator!=(Entity& other) {
			return !(*this == other);
		}; 
	private:
		entt::entity m_EntityID;
		uint64_t m_UUID;
		Scene* m_Scene;
	};
	
	
	class BSE_API ScriptableEntity {
	public:
		~ScriptableEntity(){
			m_Entity = nullptr;
		}
		
		template <typename T, typename... Args>
		T& AddComponent(Args&&... args){
			return m_Entity->AddComponent<T>(std::forward<Args>(args)...);
		}
		
		template <typename T>
		T& GetComponent(){
			return m_Entity->GetComponent<T>();
		}
		
		template <typename T>
		bool HasComponent(){
			return m_Entity->HasComponent<T>();
		}
		
		template <typename T>
		void RemoveComponent(){
			return m_Entity->RemoveComponent<T>();
		} 
		
	protected:
		virtual void OnCreate() {};
		virtual void OnDestroy() {};
		virtual void OnUpdate(float time) {};
		
	private:
		Entity* m_Entity;
		friend class Scene;
	};
}

#endif
