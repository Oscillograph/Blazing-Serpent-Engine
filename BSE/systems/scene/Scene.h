#ifndef BSE_SCENE_H
#define BSE_SCENE_H

#include <Core.h>
#include <vendor/entt/entt.hpp>
#include <renderer/GeneralCamera.h>
#include <renderer/OrthographicCamera.h>
#include <systems/GeneralCameraController.h>
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
		void DestroyEntity(Entity& entity);
		inline entt::registry& Registry() { return m_Registry; };
		inline void SetCamera(OrthographicCamera* camera) { m_Camera = camera; }
		inline OrthographicCamera* GetCamera() { return m_Camera; }
		inline void SetCameraController(GeneralCameraController* cameraController) { m_CameraController = cameraController; }
		inline GeneralCameraController* GetCameraController() { return m_CameraController; }
	protected:
		
	private:
		entt::registry m_Registry;
		
		OrthographicCamera* m_Camera = nullptr;
		GeneralCameraController* m_CameraController = nullptr;
	};
}

#endif
