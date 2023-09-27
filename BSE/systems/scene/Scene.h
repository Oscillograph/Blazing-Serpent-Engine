#ifndef BSE_SCENE_H
#define BSE_SCENE_H

#include <Core.h>
#include <vendor/entt/entt.hpp>
#include <renderer/GeneralCamera.h>
#include <renderer/OrthographicCamera.h>
#include <systems/GeneralCameraController.h>
#include <renderer/GeneralCamera.h>
#include <systems/CameraController.h>
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
		inline bool HasEntity(int entityID) { return m_Registry.valid((entt::entity)entityID); }
		
		inline void SetCamera(GeneralCamera* camera) { m_Camera = camera; }
		inline GeneralCamera* GetCamera() { return m_Camera; }
		inline void SetCameraController(CameraController* cameraController) { m_CameraController = cameraController; }
		inline CameraController* GetCameraController() { return m_CameraController; }
	protected:
		
	private:
		entt::registry m_Registry;
		
		GeneralCamera* m_Camera = nullptr;
		CameraController* m_CameraController = nullptr;
	};
}

#endif
