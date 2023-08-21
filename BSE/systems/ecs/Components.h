#ifndef BSE_COMPONENTS_H
#define BSE_COMPONENTS_H

#include <Core.h>
// #include <renderer/GeneralCamera.h>
#include <renderer/OrthographicCamera.h>
#include <systems/OrthographicCameraController.h>

namespace BSE {
	struct BSE_API NameComponent {
		std::string Name = "";
		
		NameComponent() = default;
		NameComponent(const NameComponent&) = default;
		NameComponent(const std::string& name)
			: Name(name) {};
	};
	
	struct BSE_API TransformComponent {
		glm::mat4 Transform = glm::mat4(1.0f);
		
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {};
	};
	
	struct BSE_API SpriteComponent {
		glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
		
		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			: Color(color) {};
	};
	
	struct BSE_API CameraComponent {
		OrthographicCamera Camera;
		bool Works = true;
		
		CameraComponent(){
			Camera = OrthographicCamera();
		};
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(OrthographicCamera* camera)
		: Camera(*camera) {};
		
		void TurnOn(){ Works = true; }
		void Toggle() { Works = true ? false : true; }
		void TurnOff() { Works = false; }
		
		void SetCamera(OrthographicCamera* camera, bool deletePrevious = false) {
			// if (deletePrevious)
			//	delete camera;
			Camera = *camera;
		}
		
	};
	
	struct BSE_API CameraControllerComponent {
		OrthographicCameraController* CameraController;
		
		CameraControllerComponent(const CameraControllerComponent&) = default;
		CameraControllerComponent(OrthographicCameraController* cameraController)
		: CameraController(cameraController) {};
		
		bool PlayerControlled = false;
		bool Works = true;
		
		void TurnOn(){ Works = true; }
		void Toggle() { Works = true ? false : true; }
		void TurnOff() { Works = false; }
	};
}

#endif
