#include <systems/scene/Scene.h>

#include <systems/ecs/Entity.h>
#include <systems/ecs/Components.h>

#include <renderer/Renderer2D.h>

namespace BSE {
	Scene::Scene(){
	}
	
	Scene::~Scene(){
	}
	
	Entity* Scene::CreateEntity(const std::string& name) {
		Entity* entity = new Entity( m_Registry.create(), this );
		BSE_INFO("Add default name component");
		auto& tag = entity->AddComponent<NameComponent>();
		tag.Name = name.empty() ? "Nameless entity" : name;
		BSE_INFO("Add default transform component");
		entity->AddComponent<TransformComponent>();
		BSE_INFO("Default components set");
		return entity; 
	};
	
	Entity* Scene::CreateEntityWithUUID(const std::string& name, uint64_t uuid) {
		Entity* entity = CreateEntity(name);
		if (uuid == 0) // assume that 0 is not a valid uuid
			uuid = UUID::Generate();
		auto& uuidComponent = entity->AddComponent<UUIDComponent>(uuid);
		
		BSE_INFO("UUID Component set");
		return entity; 
	};
	
	void Scene::DestroyEntity(Entity& entity){
		m_Registry.destroy(entity.GetID());
		// delete entity;
	}
	
	void Scene::OnUpdate(float sceneTime){
		// Script updating
		{
			// TODO: move to OnScenePlay;
			// TODO: build OnSceneStart; OnSceneStop; OnScenePause; OnSceneReset; OnSceneDestroy;
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc){
				if (!nsc.Instance){
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = new Entity(entity, this); // WHAT IS IT
					nsc.Instance->OnCreate();
				}
				nsc.Instance->OnUpdate(sceneTime);
			});
		}
		
		/*
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
		for (auto entity : group){
			auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
			// Renderer::Submit(sprite, transform);
			// TODO: remove temporary usage of renderer
			Renderer2D::DrawQuadGeneral(transform.Transform, nullptr, 1.0f, sprite.Color);
		}
		*/
	}
}
