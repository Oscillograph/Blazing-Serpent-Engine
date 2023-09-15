#ifndef BSE_CAMERACONTROLLER_H
#define BSE_CAMERACONTROLLER_H

#include <Core.h>
#include <renderer/GeneralCamera.h>

// events handling
#include <Input.h>
#include <KeyCodes.h>
#include <systems/events/AppEvent.h>
#include <systems/events/KeyEvent.h>
#include <systems/events/MouseEvent.h>

namespace BSE {
	struct BSE_API OrthographicCameraBounds {
		float Left, Right;
		float Top, Bottom;
		float ZNear, ZFar;
		
		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
		float GetDepth() { return ZFar - ZNear; }
	};
	
	enum class CameraProjectionType : int {
		Perspective 	= 0,
		Orthographic 	= 1
	};
	
	class BSE_API CameraController {
	public:
		CameraController() = default;
		// orthographic camera controller
		CameraController(float aspectRatio, float zoomlevel = 1.0f, bool rotation = true, bool constantAspectRatio = false);
		// perspective camera controller
		CameraController(float fov = 45.0f, float aspectRatio = 1.778f, float nearClip = 0.1f, float farClip = 1000.0f);
		
		virtual ~CameraController();
		
		// change projection types
		virtual inline CameraProjectionType GetProjectionType(){ return m_ProjectionType; }
		virtual inline void SetProjectionType(CameraProjectionType projectionType){ m_ProjectionType = projectionType; }
		
		// update projection matrix
		virtual inline void UpdateProjection(){
			switch (GetProjectionType()) {
			case CameraProjectionType::Orthographic:
				UpdateOrthographicProjection();
				break;
			case CameraProjectionType::Perspective:
				UpdatePerspectiveProjection();
				break;
			}
		}
		
		virtual void UpdatePerspectiveProjection();
		virtual void SetPerspectiveProjectionDefault();
		
		virtual void UpdateOrthographicProjection();
		virtual void SetOrthographicCameraBoundsDefault();
		virtual void SetOrthographicProjectionDefault();
		
		// update view matrix
		virtual inline void UpdateView() { 
			UpdateCameraParameters(); 
			m_Camera->Update(); 
		}
		
		virtual inline void Rotate(const glm::vec3& rotation) { m_Camera->SetRotation(rotation); }
		virtual inline void Rotate(float rotation) { m_Camera->SetRoll(rotation); }
		virtual inline glm::vec3 GetRotation() { return m_Camera->GetRotation(); }
		
		virtual inline void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = position; }
		virtual inline glm::vec3 GetCameraPosition() { return m_CameraPosition; }
		virtual inline void SetCameraTarget(const glm::vec3& target) { m_CameraTarget = target; }
		virtual inline glm::vec3 GetCameraTarget() { return m_CameraTarget; }
		
		// drop camera controller data into camera
		virtual void UpdateCameraParameters();
		
		// Perspective stuff
		virtual inline void SetPerspectiveFOV(float value){ m_PerspectiveFOV = value; UpdateProjection(); }
		virtual inline float GetPerspectiveFOV(){ return m_PerspectiveFOV; }
		
		virtual inline void SetPerspectiveNear(float value){ m_PerspectiveNear = value; UpdateProjection(); }
		virtual inline float GetPerspectiveNear(){ return m_PerspectiveNear; }
		
		virtual inline void SetPerspectiveFar(float value){ m_PerspectiveFar = value; UpdateProjection(); }
		virtual inline float GetPerspectiveFar(){ return m_PerspectiveFar; }
		
		// Orthographic stuff
		virtual inline void SetOrthographicZNear(float zNear){ m_OrthographicCameraBounds.ZNear = zNear; UpdateProjection(); }
		virtual inline float GetOrthographicZNear(){ return m_OrthographicCameraBounds.ZNear; }
		
		virtual inline void SetOrthographicZFar(float zFar){ m_OrthographicCameraBounds.ZFar = zFar; UpdateProjection(); }
		virtual inline float GetOrthographicZFar(){ return m_OrthographicCameraBounds.ZFar; }
		
		virtual inline void SetZoomLevel(float zoomLevel){ m_ZoomLevel = zoomLevel; UpdateProjection(); }
		virtual inline float GetZoomLevel() { return m_ZoomLevel; }
		
		virtual inline void SetAspectRatio(float aspectRatio){ m_AspectRatio = aspectRatio; UpdateProjection(); }
		virtual inline float GetAspectRatio() { return m_AspectRatio; }
		
		virtual inline void RefreshCamera() { UpdateProjection(); UpdateView(); m_Camera->Update(); }

		// general interface calls
		virtual inline glm::mat4 GetViewProjectionMatrix() { return m_Camera->GetViewProjectionMatrix(); }
		virtual inline glm::vec3 GetTargetToCameraDirection() { return m_TargetToCameraDirection; } 
		virtual inline OrthographicCameraBounds& GetBounds() { return m_CameraBounds; }
		
		virtual void OnUpdate(float time);
		virtual void OnResize(float width, float height);
		virtual void OnEvent(Event& e);
		
		virtual inline void SetCamera(GeneralCamera* camera, bool destroyPrevCamera = false);
		virtual inline GeneralCamera* GetCamera() { return m_Camera; }
		
		// general controller settings
		bool allowTranslation = true;
		bool allowRotation = true;
		bool allowZoom = true;
		bool constantAspectRatio = false;
		bool editorCamera = false; // is it set to be a special app camera (as in an editor)
		
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
		OrthographicCameraBounds m_OrthographicCameraBounds;
		GeneralCamera* m_Camera = nullptr;
		
		// general controller settings
		CameraProjectionType m_ProjectionType = CameraProjectionType::Perspective;
		float m_CameraRotationSpeed = 10.0f;
		float m_CameraMovementSpeed = 5.0f;
		
		// general camera settings
		float m_ViewportWidth = 0.0f;
		float m_ViewportHeight = 0.0f;
		float m_AspectRatio = 0.0f;
		float m_ZoomLevel = 0.0f; // is equivalent to size of orthographic projection
		
		float m_ViewportWidthPrev = m_ViewportWidth;
		float m_ViewportHeightPrev = m_ViewportHeight;
		float m_AspectRatioPrev = m_AspectRatio;
		
		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_CameraTarget = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_CameraRotation = {0.0f, 0.0f, 0.0f};
		glm::vec3 m_TargetToCameraDirection = {0.0f, 0.0f, 0.0f}; // = target - position
		
		// perspective stuff
		float m_PerspectiveFOV = 0.0f; // fov in degrees
		float m_PerspectiveNearClip = 0.1f; // near zone border
		float m_PerspectiveFarClip = 1000.0f; // far zone border
	};
}

#endif
