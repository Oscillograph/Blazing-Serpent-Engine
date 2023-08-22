#ifndef BSE_ORTHOGRAPHICCAMERACONTROLLER_H
#define BSE_ORTHOGRAPHICCAMERACONTROLLER_H

#include <Core.h>
//#include <Application.h>
#include <renderer/GeneralCamera.h>
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
		float ZNear, ZFar;
		
		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
		float GetDepth() { return ZFar - ZNear; }
	};
	
	class BSE_API OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, float zoomlevel = 1.0f, bool rotation = false, bool constantAspectRatio = false);
		~OrthographicCameraController();
		
		// void SetProjection(float left, float right, float top, float bottom);
		inline void SetProjectionDefault(){
			float orthoLeft 	= -m_AspectRatio * m_ZoomLevel * 0.5f;
			float orthoRight 	=  m_AspectRatio * m_ZoomLevel * 0.5f;
			float orthoTop 		=  m_ZoomLevel * 0.5f;
			float orthoBottom 	= -m_ZoomLevel * 0.5f;
			float orthoZNear 	= -2.0f;
			float orthoZFar 	=  16.0f;
			
			m_Camera->SetProjection(orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar);
			m_CameraBounds = { orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar };
		}
		
		inline void SetZoomLevel(float zoomLevel){
			m_ZoomLevel = zoomLevel;
			SetProjectionDefault();
		}
		inline float GetZoomLevel() { return m_ZoomLevel; }
		
		inline void SetAspectRatio(float aspectRatio){
			m_AspectRatio = aspectRatio;
			SetProjectionDefault();
		}
		
		inline void RefreshCamera() { SetProjectionDefault(); }
		
		inline void SetSize(float width, float height) {
			m_Width = width;
			m_Height = height;
		}
		inline void SetSize(uint32_t width, uint32_t height, float size) {
			m_Width = (float)width;
			m_Height = (float)height;
		}
		
		inline void SetConstantAspectRatio(bool isConstant) { m_ConstantAspectRatio = isConstant; }
		inline bool GetConstantAspectRatio() { return m_ConstantAspectRatio; }
		inline bool ToggleConstantAspectRatio() {
			m_ConstantAspectRatio = m_ConstantAspectRatio == true ? false : true; 
			return m_ConstantAspectRatio; 
		}
		
		inline float GetAspectRatio() { return m_AspectRatio; }
		
		inline void AllowRotation(bool isAllowed) { m_Rotation = isAllowed; }
		
		inline bool RotationStatus() { return m_Rotation; }
		
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
		
		float m_Width = 600.0f;
		float m_Height = 400.0f;
		float m_Size = 10.0f;
		
		// GeneralCamera* m_Camera;
		OrthographicCamera* m_Camera;
		
		bool m_Rotation;
		bool m_ConstantAspectRatio = true;
		
		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		float m_CameraMoveSpeed = 5.0f;
		float m_CameraRotateSpeed = 10.0f;
		
		OrthographicCameraBounds m_CameraBounds;
	};
}

#endif
