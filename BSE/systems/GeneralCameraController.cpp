#include <systems/GeneralCameraController.h>

namespace BSE {
	GeneralCameraController::GeneralCameraController(float aspectRatio, float zoomlevel, bool rotation, bool constantAspectRatio){
		BSE_CORE_TRACE("Calling Camera Controller constructor");
		m_AspectRatio = aspectRatio;
		m_AspectRatioPrev = m_AspectRatio;
		m_ZoomLevel = zoomlevel;
		// m_Size = size;
		m_Rotate = rotation;
		m_ConstantAspectRatio = constantAspectRatio;
		m_ProjectionType = CameraProjectionType::Orthographic;
		m_EditorCamera = false;
		
		float orthoLeft 	= -m_AspectRatio * m_ZoomLevel * 0.5f;
		float orthoRight 	=  m_AspectRatio * m_ZoomLevel * 0.5f;
		float orthoTop 		=  m_ZoomLevel * 0.5f;
		float orthoBottom 	= -m_ZoomLevel * 0.5f;
		float orthoZNear 	= -2.0f;
		float orthoZFar 	=  16.0f;
		
		// m_Camera->SetProjection(orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar);
		m_CameraBounds = { orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar };
		
		m_Camera = new OrthographicCamera(
			m_CameraBounds.Left, 
			m_CameraBounds.Right, 
			m_CameraBounds.Top, 
			m_CameraBounds.Bottom, 
			m_CameraBounds.ZNear, 
			m_CameraBounds.ZFar);
		BSE_CORE_TRACE("General Camera Controller constructor: Orthographic Camera created");
		m_CameraPosition = m_Camera->GetPosition();
		BSE_CORE_TRACE("General Camera Controller constructor: Orthographic Camera position taken");
	}
	
	GeneralCameraController::GeneralCameraController(float fov, float aspectRatio, float znear, float zfar)
	// : OrthographicCameraController(0, 0) // use parent dummy contructor to prevent it from doing harm here
	{
		BSE_CORE_TRACE("Calling Editor Camera Controller constructor");
		m_PerspectiveVerticalFOV = glm::radians(fov);
		m_PerspectiveHorizontalFOV = m_PerspectiveVerticalFOV;
		m_AspectRatio = aspectRatio;
		m_AspectRatioPrev = m_AspectRatio;
		m_ZoomLevel = 10.0f;
		// m_Size = size;
		m_Rotate = true;
		m_ConstantAspectRatio = false;
		m_ProjectionType = CameraProjectionType::Perspective;
		// m_EditorCamera = true;
		
		float orthoLeft 	= -m_AspectRatio * m_ZoomLevel * 0.5f;
		float orthoRight 	=  m_AspectRatio * m_ZoomLevel * 0.5f;
		float orthoTop 		=  m_ZoomLevel * 0.5f;
		float orthoBottom 	= -m_ZoomLevel * 0.5f;
		float orthoZNear 	= -2.0f;
		float orthoZFar 	=  16.0f;
		
		// m_Camera->SetProjection(orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar);
		m_CameraBounds = { orthoLeft, orthoRight, orthoTop, orthoBottom, orthoZNear, orthoZFar };
		
		m_Camera = new EditorCamera(
			m_PerspectiveVerticalFOV, 
			m_AspectRatio, 
			m_CameraBounds.ZNear, 
			m_CameraBounds.ZFar);
		
		m_CameraPosition = m_Camera->GetPosition();
	}
	
	GeneralCameraController::~GeneralCameraController(){
		
	}
	
	void GeneralCameraController::OnUpdate(float time){
		if (m_EditorCamera) {
			EditorCamera* cam = (EditorCamera*)m_Camera;
			cam->OnUpdate(time);
		} else {
			m_CameraPosition = m_Camera->GetPosition();
			if (Input::IsKeyPressed(BSE_KEY_W)){
				m_CameraPosition.y += m_CameraMoveSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_A)){
				m_CameraPosition.x -= m_CameraMoveSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_S)){
				m_CameraPosition.y -= m_CameraMoveSpeed * time;
			}
			if (Input::IsKeyPressed(BSE_KEY_D)){
				m_CameraPosition.x += m_CameraMoveSpeed * time;
			}
			
			m_Camera->SetPosition(m_CameraPosition);
			
			if (m_Rotate){
				glm::vec3 rotation = m_Camera->GetRotation();
				if (Input::IsKeyPressed(BSE_KEY_UP)){
					rotation.z -= m_CameraRotateSpeed * time;
				}
				if (Input::IsKeyPressed(BSE_KEY_DOWN)){
					rotation.z += m_CameraRotateSpeed * time;
				}
				if (Input::IsKeyPressed(BSE_KEY_LEFT)){
					rotation.x -= m_CameraRotateSpeed * time;
				}
				if (Input::IsKeyPressed(BSE_KEY_RIGHT)){
					rotation.x += m_CameraRotateSpeed * time;
				}
				m_Camera->SetRotation(rotation);
			}
			
			if (Input::IsKeyPressed(BSE_KEY_PAGE_UP)){
				m_ZoomLevel -= 0.1f;
				SetProjectionDefault();
			}
			if (Input::IsKeyPressed(BSE_KEY_PAGE_DOWN)){
				m_ZoomLevel += 0.1f;
				SetProjectionDefault();
			}
		}
	}
	
	void GeneralCameraController::OnResize(float width, float height) {
		if ((width > 0.0f) && height > 0.0f){
			m_Width = width;
			m_Height = height;
			
			// BSE_INFO("CameraControl_OnResize - Aspect Ratio is constant: {0}", GetConstantAspectRatio());
			// BSE_INFO("DLL Adress: {}", fmt::ptr(this));
			
			if (GetConstantAspectRatio()){
				// BSE_INFO("Aspect Ratio is set to be constant");
				m_AspectRatio = m_AspectRatioPrev;
				// m_ZoomLevel = m_ZoomLevel;
			} else {
				// BSE_INFO("Width: {0}, Height: {1}", width, height);
				m_AspectRatio = width / height;
			}
			
			// m_ZoomLevel = m_ZoomLevel * m_AspectRatio / m_AspectRatioPrev;
			m_AspectRatioPrev = m_AspectRatio;
			m_HeightPrev = width;
			m_WidthPrev = height;
			
			SetProjectionDefault();
		}
	}
	
	void GeneralCameraController::OnEvent(Event& e){
		if (m_EditorCamera) {
			EditorCamera* cam = (EditorCamera*)m_Camera;
			cam->OnEvent(e);
		} else {
			EventDispatcher dispatcher(e);
			
			dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){
				return OnMouseScrolled(event);
			});
			
			dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event){
				return OnWindowResized(event);
			});
		}
	}
	
	bool GeneralCameraController::OnMouseScrolled(MouseScrolledEvent& e){
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		//m_ZoomLevel = (m_ZoomLevel < m_ZoomMin) ? (m_ZoomMin) : m_ZoomLevel;
		//m_ZoomLevel = (m_ZoomLevel > m_ZoomMax) ? (m_ZoomMax) : m_ZoomLevel;
		
		SetProjectionDefault();
		
		return false;
	}
	
	bool GeneralCameraController::OnWindowResized(WindowResizeEvent& e){
		float widthNew = (float)(e.GetWidth());
		float heightNew = (float)(e.GetHeight());
		
		OnResize(widthNew, heightNew);
		return false;
	}
}
