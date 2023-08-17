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
	
	void Scene::OnUpdate(float sceneTime){
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
		for (auto entity : group){
			auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
			// Renderer::Submit(sprite, transform);
			// TODO: remove temporary usage of renderer
			Renderer2D::DrawQuadGeneral(transform.Transform, nullptr, 1.0f, sprite.Color);
		}
	}
}
