#ifndef BSE_GENERALCAMERACONTROLLER_H
#define BSE_GENERALCAMERACONTROLLER_H

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
	
	class BSE_API GeneralCameraController {
	public:
		GeneralCameraController() = default;
		GeneralCameraController(int, int){}; // dummy constructor to be called specifically to prevent from parent corrupt a child
		GeneralCameraController(float aspectRatio, float zoomlevel = 1.0f, bool rotation = false, bool constantAspectRatio = false);
		virtual ~GeneralCameraController();
		
		virtual inline CameraProjectionType GetProjectionType(){ return m_ProjectionType; }
		virtual inline void SetProjectionType(CameraProjectionType projectionType){ m_ProjectionType = projectionType; }
		
		// Perspective stuff
		virtual inline float GetPerspectiveVerticalFOV(){ return m_PerspectiveVerticalFOV; }
		virtual inline float GetPerspectiveHorizontalFOV(){ return m_PerspectiveHorizontalFOV; }
		virtual inline float GetPerspectiveNear(){ return m_PerspectiveNear; }
		virtual inline float GetPerspectiveFar(){ return m_PerspectiveFar; }
		
		virtual inline void SetPerspectiveVerticalFOV(float value){ m_PerspectiveVerticalFOV = value; SetProjectionDefault(); }
		virtual inline void SetPerspectiveHorizontalFOV(float value){ m_PerspectiveHorizontalFOV = value; SetProjectionDefault(); }
		virtual inline void SetPerspectiveNear(float value){ m_PerspectiveNear = value; SetProjectionDefault(); }
		virtual inline void SetPerspectiveFar(float value){ m_PerspectiveFar = value; SetProjectionDefault(); }
		
		// Orthographic stuff
		virtual inline float GetOrthographicZNear(){ return m_CameraBounds.ZNear; }
		virtual inline void SetOrthographicZNear(float zNear){ 
			m_CameraBounds.ZNear = zNear;
			m_Camera->SetProjection(
				m_CameraBounds.Left, m_CameraBounds.Right, 
				m_CameraBounds.Top, m_CameraBounds.Bottom, 
				m_CameraBounds.ZNear, m_CameraBounds.ZFar
				);
		}
		
		virtual inline float GetOrthographicZFar(){ return m_CameraBounds.ZFar; }
		virtual inline void SetOrthographicZFar(float zFar){ 
			m_CameraBounds.ZFar = zFar;
			m_Camera->SetProjection(
				m_CameraBounds.Left, m_CameraBounds.Right, 
				m_CameraBounds.Top, m_CameraBounds.Bottom, 
				m_CameraBounds.ZNear, m_CameraBounds.ZFar
				);
		}
		
		// void SetProjection(float left, float right, float top, float bottom);
		virtual inline void SetOrthographicProjectionDefault(){
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
		
		virtual inline void SetPerspectiveProjectionDefault(){
			glm::mat4 projection = glm::perspective(
				glm::radians(m_PerspectiveVerticalFOV), 
				m_AspectRatio, 
				m_PerspectiveNear,
				m_PerspectiveFar
				);
			m_Camera->SetProjection(projection);
		}
		
		virtual inline void SetProjectionDefault(){
			switch (GetProjectionType()) {
			case CameraProjectionType::Orthographic:
				SetOrthographicProjectionDefault();
				break;
			case CameraProjectionType::Perspective:
				SetPerspectiveProjectionDefault();
				break;
			}
		}
		
		virtual inline void SetZoomLevel(float zoomLevel){
			m_ZoomLevel = zoomLevel;
			SetProjectionDefault();
		}
		virtual inline float GetZoomLevel() { return m_ZoomLevel; }
		
		virtual inline void SetAspectRatio(float aspectRatio){
			m_AspectRatio = aspectRatio;
			SetProjectionDefault();
		}
		
		virtual inline void RefreshCamera() { SetProjectionDefault(); }
		
		virtual inline void SetSize(float width, float height) {
			m_Width = width;
			m_Height = height;
		}
		virtual inline void SetSize(uint32_t width, uint32_t height, float size) {
			m_Width = (float)width;
			m_Height = (float)height;
		}
		
		virtual inline void SetConstantAspectRatio(bool isConstant) { m_ConstantAspectRatio = isConstant; }
		virtual inline bool GetConstantAspectRatio() { return m_ConstantAspectRatio; }
		virtual inline bool ToggleConstantAspectRatio() {
			m_ConstantAspectRatio = m_ConstantAspectRatio == true ? false : true; 
			return m_ConstantAspectRatio; 
		}
		
		virtual inline float GetAspectRatio() { return m_AspectRatio; }
		
		virtual inline void AllowRotation(bool isAllowed) { m_Rotation = isAllowed; }
		virtual inline bool RotationStatus() { return m_Rotation; }
		virtual inline void Rotate(const glm::vec3& rotation) { m_Camera->SetRotation(rotation); }
		virtual inline void Rotate(float rotation) { m_Camera->SetRotation(rotation); }
		
		virtual inline OrthographicCameraBounds& GetBounds() { return m_CameraBounds; }
		
		virtual void OnUpdate(float time);
		virtual void OnResize(float width, float height);
		virtual void OnEvent(Event& e);
	
		virtual inline OrthographicCamera* GetCamera() { return m_Camera; }
		virtual inline void SetCamera(OrthographicCamera* camera, bool destroyPrevCamera = false) {
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
