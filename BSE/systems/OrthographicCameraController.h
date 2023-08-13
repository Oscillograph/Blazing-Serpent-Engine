#ifndef BSE_ORTHOGRAPHICCAMERACONTROLLER_H
#define BSE_ORTHOGRAPHICCAMERACONTROLLER_H

#include <Core.h>
//#include <Application.h>
#include <renderer/OrthographicCamera.h>

#include <Input.h>
#include <KeyCodes.h>
#include <systems/events/AppEvent.h>
#include <systems/events/KeyEvent.h>
#include <systems/events/MouseEvent.h>

namespace BSE {
	struct BSE_API OrthographicCameraBounds {
		float Left, Right;
		float Top, Bottom;
		
		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
	
	class BSE_API OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, float zoomLevel = 1.0f, bool rotation = false); 
		~OrthographicCameraController();
		
		// void SetProjection(float left, float right, float top, float bottom);
		inline void SetProjectionDefault(){
			m_Camera->SetProjection(
				-m_AspectRatio * m_ZoomLevel,
				 m_AspectRatio * m_ZoomLevel,
				 m_ZoomLevel,
				-m_ZoomLevel
				);
			m_CameraBounds = {
				-m_AspectRatio * m_ZoomLevel, 
				 m_AspectRatio * m_ZoomLevel, 
				 m_ZoomLevel, 
				-m_ZoomLevel 
			};
		}
		inline void SetZoomLevel(float zoomLevel){
			m_ZoomLevel = zoomLevel;
			SetProjectionDefault();
		}
		inline float GetZoomLevel(){ return m_ZoomLevel; }
		
		inline void SetAspectRatio(float aspectRatio){
			m_AspectRatio = aspectRatio;
			SetProjectionDefault();
		}
		inline float GetAspectRatio(){ return m_AspectRatio; }
		
		inline const OrthographicCameraBounds& GetBounds() const { return m_CameraBounds; }
		
		void OnUpdate(float time);
		void OnResize(float width, float height);
		void OnEvent(Event& e);
	
		inline OrthographicCamera* GetCamera() { return m_Camera; }
		inline void SetCamera(OrthographicCamera* camera, bool destroyPrevCamera = false) {
			if (destroyPrevCamera && (m_Camera != nullptr)){
				delete m_Camera;
			}
			m_Camera = camera; 
		}
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
		float m_AspectRatio = 1.0f;
		float m_AspectRatioPrev = 1.0f;
		float m_WidthPrev = 0.0f;
		float m_HeightPrev = 0.0f;
		
		float m_ZoomLevel = 1.0f;
		float m_ZoomMin = -2.0f;
		float m_ZoomMax = 2.0f;
		OrthographicCamera* m_Camera;
		
		bool m_Rotation;
		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		float m_CameraMoveSpeed = 5.0f;
		float m_CameraRotateSpeed = 10.0f;
		
		OrthographicCameraBounds m_CameraBounds;
	};
}

#endif
