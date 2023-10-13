#ifndef BSE_COMPONENTS_H
#define BSE_COMPONENTS_H

#include <Core.h>
// #include <renderer/GeneralCamera.h>
#include <renderer/Texture.h>
#include <renderer/OrthographicCamera.h>
#include <systems/GeneralCameraController.h>
#include <renderer/GeneralCamera.h>
#include <systems/CameraController.h>

#include <systems/scene/UUID.h>

namespace BSE {
	struct BSE_API NameComponent {
		std::string Name = "";
		
		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name)
			: Name(name) {};
	};
	
	struct BSE_API UUIDComponent {
		uint64_t ID = 0;
		
		UUIDComponent() 
			: ID(UUID::Generate()) 
		{};
		
		UUIDComponent(const UUIDComponent&) = default;
		
		UUIDComponent(const uint64_t& uuid)
			: ID(uuid) 
		{};
		
	};
	
	struct BSE_API TransformComponent {
		// glm::mat4 Transform = glm::mat4(1.0f);
		glm::vec3 Translation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
		glm::vec3 Scale = {1.0f, 1.0f, 1.0f};
		
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {};
		
		glm::mat4 GetTransform() {
			glm::mat4 rotation = 
				glm::rotate(OneMat4, Rotation.x, {1, 0, 0}) *
				glm::rotate(OneMat4, Rotation.y, {0, 1, 0}) *
				glm::rotate(OneMat4, Rotation.z, {0, 0, 1});
			
			return glm::translate(OneMat4,Translation) * rotation * glm::scale(OneMat4, Scale);
		}
	};
	
	struct BSE_API SpriteComponent {
		glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
		Texture2D* Texture = nullptr;
		float TilingFactor = 1.0f;
		
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			: Color(color) {};
	};
	
	struct BSE_API CameraComponent {
		GeneralCamera Camera;
		bool Works = true;
		
		CameraComponent(){
			Camera = GeneralCamera();
		};
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(GeneralCamera* camera)
		: Camera(*camera) {};
		
		void TurnOn(){ Works = true; }
		void Toggle() { Works = true ? false : true; }
		void TurnOff() { Works = false; }
		
		void SetCamera(GeneralCamera* camera, bool deletePrevious = false) {
			// if (deletePrevious)
			//	delete camera;
			Camera = *camera;
		}
		
	};
	
	struct BSE_API CameraControllerComponent {
		CameraController* cameraController = nullptr;
		
		CameraControllerComponent(const CameraControllerComponent&) = default;
		CameraControllerComponent(float aspectRatio, float zoomLevel = 1.0f, bool rotation = false, bool constantAspectRatio = false){
			cameraController = new CameraController(aspectRatio, zoomLevel, rotation, constantAspectRatio);
			// BSE_INFO("Component initialized with CameraController at {}", fmt::ptr(CameraController));
		};
		CameraControllerComponent(CameraController* controller){
			cameraController = controller;
			// BSE_INFO("Component initialized with CameraController at {}", fmt::ptr(CameraController));
			// BSE_INFO("The passed argument points at: {}", fmt::ptr(cameraController));
		};
		
		bool PlayerControlled = false;
		bool Works = true;
		
		void TurnOn(){ Works = true; }
		void Toggle() { Works = true ? false : true; }
		void TurnOff() { Works = false; }
	};
	
	struct BSE_API NativeScriptComponent {
		ScriptableEntity* Instance = nullptr;
		
		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);
		
		template <typename T>
		void Bind() {
			InstantiateScript = [](){
				return static_cast<ScriptableEntity*>(new T());
			};
			
			DestroyScript = [](NativeScriptComponent* nsc){
				delete nsc->Instance;
				nsc->Instance = nullptr;
			};
		}
	};
}

#endif
