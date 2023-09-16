#include <systems/CameraController.h>

namespace BSE {
	CameraController::CameraController(float aspectRatio, float zoomlevel, bool rotation, bool constantAspectRatio){
		BSE_CORE_TRACE("Calling Camera Controller constructor");
		m_AspectRatio = aspectRatio;
		m_AspectRatioPrev = m_AspectRatio;
		m_ZoomLevel = zoomlevel;
		m_ProjectionType = CameraProjectionType::Orthographic;
		
		allowRotation = rotation;
		constantAspectRatio = constantAspectRatio;
		editorCamera = false;
		
		SetOrthographicProjectionDefault();

		m_ViewportWidth = m_OrthographicCameraBounds.GetWidth();
		m_ViewportHeight = m_OrthographicCameraBounds.GetHeight();
		
		m_Camera = new GeneralCamera(
			m_OrthographicCameraBounds.Left, 
			m_OrthographicCameraBounds.Right, 
			m_OrthographicCameraBounds.Top, 
			m_OrthographicCameraBounds.Bottom, 
			m_OrthographicCameraBounds.ZNear, 
			m_OrthographicCameraBounds.ZFar);
		
		BSE_CORE_TRACE("Camera Controller constructor: Orthographic Camera created");
		m_CameraPosition = m_Camera->GetPosition();
		BSE_CORE_TRACE("Camera Controller constructor: Orthographic Camera position taken");
	}
	
	CameraController::CameraController(float fov, float aspectRatio, float nearClip, float farClip){
		BSE_CORE_TRACE("Calling Editor Camera Controller constructor");
		m_PerspectiveFOV = fov;
		m_AspectRatio = aspectRatio;
		m_PerspectiveNearClip = nearClip;
		m_PerspectiveFarClip = farClip;
		m_ZoomLevel = 10.0f;
		
		m_AspectRatioPrev = m_AspectRatio;
		
		allowRotation = true;
		allowTranslation = true;
		allowZoom = true;
		constantAspectRatio = false;
		m_ProjectionType = CameraProjectionType::Perspective;
		editorCamera = false;
		
		m_Camera = new GeneralCamera(
			m_PerspectiveFOV, 
			m_AspectRatio, 
			m_OrthographicCameraBounds.ZNear, 
			m_OrthographicCameraBounds.ZFar);
		
		BSE_CORE_TRACE("General Camera Controller constructor: Perspective Camera created");
		m_CameraPosition = m_Camera->GetPosition();
		m_CameraTarget = m_Camera->GetTarget();
		m_CameraRotation = m_Camera->GetRotation();
		BSE_CORE_TRACE("General Camera Controller constructor: Perspective Camera parameters taken");
	}
	
	CameraController::~CameraController(){
		// default virtual destructor
	}
	
	void CameraController::UpdatePerspectiveProjection(){
		m_Camera->SetProjection({
			glm::perspective(
				glm::radians(m_PerspectiveFOV), 
				m_AspectRatio, 
				m_PerspectiveNearClip,
				m_PerspectiveFarClip
				)
			});
	}
	
	void CameraController::SetPerspectiveProjectionDefault(){
		m_PerspectiveFOV = 45.0f;
		m_AspectRatio = 1.778f;
		m_PerspectiveNearClip = 0.1f;
		m_PerspectiveFarClip = 1000.f;
		
		UpdatePerspectiveProjection();
	}
	
	void CameraController::UpdateOrthographicProjection(){
		m_Camera->SetProjection(
			m_OrthographicCameraBounds.Left, m_OrthographicCameraBounds.Right, 
			m_OrthographicCameraBounds.Top, m_OrthographicCameraBounds.Bottom, 
			m_OrthographicCameraBounds.ZNear, m_OrthographicCameraBounds.ZFar
			);
	}
	
	void CameraController::SetOrthographicCameraBoundsDefault(){
		m_OrthographicCameraBounds.Left 	= -m_AspectRatio * m_ZoomLevel * 0.5f;
		m_OrthographicCameraBounds.Right 	=  m_AspectRatio * m_ZoomLevel * 0.5f;
		m_OrthographicCameraBounds.Top 		=  m_ZoomLevel * 0.5f;
		m_OrthographicCameraBounds.Bottom 	= -m_ZoomLevel * 0.5f;
		m_OrthographicCameraBounds.ZNear 	= -2.0f;
		m_OrthographicCameraBounds.ZFar 	=  16.0f;
	}
	
	void CameraController::SetOrthographicProjectionDefault(){
		SetOrthographicCameraBoundsDefault();
		UpdateOrthographicProjection();
	}
	
	void CameraController::UpdateCameraParameters() {
		// target
		m_Camera->SetTarget(m_CameraTarget);
		
		// translation
		if (allowTranslation) {
			m_Camera->SetPosition(m_CameraPosition);
		}
		
		// rotation
		if (allowRotation) {
			if (m_CameraRotation.y > 89.0f)
				m_CameraRotation.y = 89.0f;
			if (m_CameraRotation.y < -89.0f)
				m_CameraRotation.y = -89.0f;
			
			m_Camera->SetRotation(m_CameraRotation);
			// TODO: Understand and rewrite to make camera rotate cleanly
			m_TargetToCameraDirection.x = cosf(glm::radians(m_CameraRotation.y)) * cosf(glm::radians(m_CameraRotation.x));
			m_TargetToCameraDirection.y = sinf(glm::radians(m_CameraRotation.x));
			m_TargetToCameraDirection.z = sinf(glm::radians(m_CameraRotation.y)) * cosf(glm::radians(m_CameraRotation.x));
		}
		m_TargetToCameraDirection = glm::normalize(m_CameraPosition - m_CameraTarget);
		
		// zoom
		if (allowZoom){
			if (m_ZoomLevel < 0.1f)
				m_ZoomLevel = 0.1f;
			m_Camera->SetDistance(m_ZoomLevel);
		}
		
		// perspective data
		m_Camera->fov = m_PerspectiveFOV;
		m_Camera->nearClip = m_PerspectiveNearClip;
		m_Camera->farClip = m_PerspectiveFarClip;
		
		// misc
		m_Camera->aspectRatio = m_AspectRatio;
		
		if (m_ProjectionType == CameraProjectionType::Perspective)
			m_Camera->perspective = true;
		if (m_ProjectionType == CameraProjectionType::Orthographic)
			m_Camera->perspective = false;
		
		m_Camera->cameraControllerData.allowRotation = allowRotation;
		m_Camera->cameraControllerData.allowTranslation = allowTranslation;
		m_Camera->cameraControllerData.allowZoom = allowZoom;
		m_Camera->cameraControllerData.constantAspectRatio = constantAspectRatio;
		m_Camera->cameraControllerData.editorCamera = editorCamera;
		m_Camera->cameraControllerData.m_CameraMovementSpeed = m_CameraMovementSpeed;
		m_Camera->cameraControllerData.m_CameraRotationSpeed = m_CameraRotationSpeed;
		m_Camera->cameraControllerData.m_ViewportHeight = m_ViewportHeight;
		m_Camera->cameraControllerData.m_ViewportWidth = m_ViewportWidth;
		m_Camera->cameraControllerData.m_ZoomLevel = m_ZoomLevel;
	}
	
	void CameraController::SetCamera(GeneralCamera* camera, bool destroyPrevCamera) {
		if (destroyPrevCamera && (m_Camera != nullptr)){
			delete m_Camera;
		} else {
			UpdateCameraParameters();
		}
		m_Camera = camera; 
		
		m_CameraPosition = m_Camera->GetPosition();
		m_CameraTarget = m_Camera->GetTarget();
		m_CameraRotation = m_Camera->GetRotation();
		m_TargetToCameraDirection = m_CameraTarget - m_CameraPosition;
		
		m_PerspectiveFOV = m_Camera->fov;
		m_PerspectiveNearClip = m_Camera->nearClip;
		m_PerspectiveFarClip = m_Camera->farClip;
		
		m_ViewportWidth = m_Camera->cameraControllerData.m_ViewportWidth;
		m_ViewportHeight = m_Camera->cameraControllerData.m_ViewportHeight;
		m_AspectRatio = m_Camera->aspectRatio;
		m_ZoomLevel = m_Camera->cameraControllerData.m_ZoomLevel;
		
		m_CameraMovementSpeed = m_Camera->cameraControllerData.m_CameraMovementSpeed;
		m_CameraRotationSpeed = m_Camera->cameraControllerData.m_CameraRotationSpeed;
		
		editorCamera = m_Camera->cameraControllerData.editorCamera;
		allowRotation = m_Camera->cameraControllerData.allowRotation;
		allowTranslation = m_Camera->cameraControllerData.allowTranslation;
		allowZoom = m_Camera->cameraControllerData.allowZoom;
	}
	
	void CameraController::OnUpdate(float time){
		if (Input::IsKeyPressed(BSE_KEY_W)){
			m_CameraPosition.y += m_CameraMovementSpeed * time;
		}
		if (Input::IsKeyPressed(BSE_KEY_A)){
			m_CameraPosition.x -= m_CameraMovementSpeed * time;
		}
		if (Input::IsKeyPressed(BSE_KEY_S)){
			m_CameraPosition.y -= m_CameraMovementSpeed * time;
		}
		if (Input::IsKeyPressed(BSE_KEY_D)){
			m_CameraPosition.x += m_CameraMovementSpeed * time;
		}
		
		m_Camera->SetPosition(m_CameraPosition);
		
		if (allowRotation){
			// glm::vec3 rotation = m_Camera->GetRotation();
			if (Input::IsKeyPressed(BSE_KEY_UP)){
				m_CameraRotation.z -= m_CameraRotationSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_DOWN)){
				m_CameraRotation.z += m_CameraRotationSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_LEFT)){
				m_CameraRotation.x -= m_CameraRotationSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_RIGHT)){
				m_CameraRotation.x += m_CameraRotationSpeed * time;
			}
			m_Camera->SetRotation(m_CameraRotation);
		}
		
		if (Input::IsKeyPressed(BSE_KEY_PAGE_UP)){
			m_ZoomLevel -= 0.1f;
		}
		if (Input::IsKeyPressed(BSE_KEY_PAGE_DOWN)){
			m_ZoomLevel += 0.1f;
		}
		
		UpdateView();
	}
	
	void CameraController::OnResize(float width, float height) {
		if ((width > 0.0f) && height > 0.0f){
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			
			if (constantAspectRatio){
				m_AspectRatio = m_AspectRatioPrev;
			} else {
				m_AspectRatio = width / height;
			}
			
			m_AspectRatioPrev = m_AspectRatio;
			m_ViewportHeightPrev = width;
			m_ViewportWidthPrev = height;
			
			UpdateProjection();
		}
	}
	
	void CameraController::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){
			return OnMouseScrolled(event);
		});
		
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event){
			return OnWindowResized(event);
		});
	}
	
	bool CameraController::OnMouseScrolled(MouseScrolledEvent& e){
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		//m_ZoomLevel = (m_ZoomLevel < m_ZoomMin) ? (m_ZoomMin) : m_ZoomLevel;
		//m_ZoomLevel = (m_ZoomLevel > m_ZoomMax) ? (m_ZoomMax) : m_ZoomLevel;
		
		UpdateView();
		
		return false;
	}
	
	bool CameraController::OnWindowResized(WindowResizeEvent& e){
		float widthNew = (float)(e.GetWidth());
		float heightNew = (float)(e.GetHeight());
		
		OnResize(widthNew, heightNew);
		return false;
	}
}
