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
	
	enum class CameraProjectionType : int {
		Perspective 	= 0,
		Orthographic 	= 1
	};
	
	class BSE_API OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, float zoomlevel = 1.0f, bool rotation = false, bool constantAspectRatio = false);
		~OrthographicCameraController();
		
		inline CameraProjectionType GetProjectionType(){ return m_ProjectionType; }
		inline void SetProjectionType(CameraProjectionType projectionType){ m_ProjectionType = projectionType; }
		
		// Perspective stuff
		inline float GetPerspectiveVerticalFOV(){ return m_PerspectiveVerticalFOV; }
		inline float GetPerspectiveHorizontalFOV(){ return m_PerspectiveHorizontalFOV; }
		inline float GetPerspectiveNear(){ return m_PerspectiveNear; }
		inline float GetPerspectiveFar(){ return m_PerspectiveFar; }
		
		inline void SetPerspectiveVerticalFOV(float value){ m_PerspectiveVerticalFOV = value; SetProjectionDefault(); }
		inline void SetPerspectiveHorizontalFOV(float value){ m_PerspectiveHorizontalFOV = value; SetProjectionDefault(); }
		inline void SetPerspectiveNear(float value){ m_PerspectiveNear = value; SetProjectionDefault(); }
		inline void SetPerspectiveFar(float value){ m_PerspectiveFar = value; SetProjectionDefault(); }
		
		// Orthographic stuff
		inline float GetOrthographicZNear(){ return m_CameraBounds.ZNear; }
		inline void SetOrthographicZNear(float zNear){ 
			m_CameraBounds.ZNear = zNear;
			m_Camera->SetProjection(
				m_CameraBounds.Left, m_CameraBounds.Right, 
				m_CameraBounds.Top, m_CameraBounds.Bottom, 
				m_CameraBounds.ZNear, m_CameraBounds.ZFar
				);
		}
		
		inline float GetOrthographicZFar(){ return m_CameraBounds.ZFar; }
		inline void SetOrthographicZFar(float zFar){ 
			m_CameraBounds.ZFar = zFar;
			m_Camera->SetProjection(
				m_CameraBounds.Left, m_CameraBounds.Right, 
				m_CameraBounds.Top, m_CameraBounds.Bottom, 
				m_CameraBounds.ZNear, m_CameraBounds.ZFar
				);
		}
		
		// void SetProjection(float left, float right, float top, float bottom);
		inline void SetOrthographicProjectionDefault(){
			m_CameraBounds.Left 	= -m_AspectRatio * m_ZoomLevel * 0.5f;
			m_CameraBounds.Right 	=  m_AspectRatio * m_ZoomLevel * 0.5f;
			m_CameraBounds.Top 		=  m_ZoomLevel * 0.5f;
			m_CameraBounds.Bottom 	= -m_ZoomLevel * 0.5f;
			m_CameraBounds.ZNear 	= -2.0f;
			m_CameraBounds.ZFar 	=  16.0f;
			
			m_Camera->SetProjection(
				m_CameraBounds.Left, m_CameraBounds.Right, 
				m_CameraBounds.Top, m_CameraBounds.Bottom, 
				m_CameraBounds.ZNear, m_CameraBounds.ZFar
				);
		}
		
		inline void SetPerspectiveProjectionDefault(){
			glm::mat4 projection = glm::perspective(
				glm::radians(m_PerspectiveVerticalFOV), 
				m_AspectRatio, 
				m_PerspectiveNear,
				m_PerspectiveFar
				);
			m_Camera->SetProjection(projection);
		}
		
		inline void SetProjectionDefault(){
			switch (GetProjectionType()) {
			case CameraProjectionType::Orthographic:
				SetOrthographicProjectionDefault();
				break;
			case CameraProjectionType::Perspective:
				SetPerspectiveProjectionDefault();
				break;
			}
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
		inline void Rotate(const glm::vec3& rotation) { m_Camera->SetRotation(rotation); }
		inline void Rotate(float rotation) { m_Camera->SetRotation(rotation); }
		
		inline OrthographicCameraBounds& GetBounds() { return m_CameraBounds; }
		
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
		CameraProjectionType m_ProjectionType;
		
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
		
		// Perspective stuff
		float m_PerspectiveHorizontalFOV = 60.0f;
		float m_PerspectiveVerticalFOV = 45.0f;
		float m_PerspectiveNear = 0.01f;
		float m_PerspectiveFar = 1000.0f;
	};
}

#endif
