#include <systems/scene/Scene.h>
#include <renderer/Renderer2D.h>

namespace BSE {
	/*
	static void DoMaths(const glm::mat4& transform){
		
	}
	
	static void OnTransformComponentConstruct(entt::registry& registry, entt::entity entity){
		
	}
	
	struct MeshComponent {};
	struct TransformComponent {
		glm::mat4 Transform;
		
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
		: Transform(Transform) {};
		
		operator glm::mat4& () {return Transform};
		operator const glm::mat4& () const {return Transform};
	};
	
	TransformComponent transform;
	DoMaths(transform);
	
	entt::entity entity = m_Registry.create();
	
	auto& transform = m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	m_Registry.get(entity)
	if (m_Registry.has<TransformComponent>(entity))
		TransformComponent& transform = m_Registry.remove<TransformComponent>(entity);
	
	auto view = m_Registry.view<TransformComponent>();
	for (auto entity : view){
		view.get<MeshComponent>()
	}
	
	auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
	for (auto entity : group){
		auto&[transform, mesh] TransformComponent& transform = group.get<TransformComponent, MeshComponent>(entity);
		Renderer::Submit(mesh, transform);
	}
	
	m_Registry.on_construct<TransformComponent>().connect<&OnTransformComponentConstruct>();
	*/
	
	Scene::Scene(){
	}
	
	Scene::~Scene(){
	}
	
	void Scene::OnUpdate(float sceneTime){
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
		for (auto entity : group){
			auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
			// Renderer::Submit(sprite, transform);
			Renderer2D::DrawQuadGeneral(transform.Transform, nullptr, 1.0f, sprite.Color);
		}
	}
}
