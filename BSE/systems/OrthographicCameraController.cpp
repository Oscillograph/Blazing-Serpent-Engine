#include <systems/OrthographicCameraController.h>

namespace BSE {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel, bool rotation){
		m_AspectRatio = aspectRatio;
		m_ZoomLevel = zoomLevel;
		m_Rotation = rotation;
		
		m_Camera = new OrthographicCamera(
			-m_AspectRatio * m_ZoomLevel,
			 m_AspectRatio * m_ZoomLevel,
			 m_ZoomLevel,
			-m_ZoomLevel
			);
		
		m_CameraPosition = m_Camera->GetPosition();
	} 
	
	OrthographicCameraController::~OrthographicCameraController(){
		
	}
	
	void OrthographicCameraController::OnUpdate(float time){
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
		
		if (m_Rotation){
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
	}
	
	void OrthographicCameraController::OnEvent(Event& e){
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){
			return OnMouseScrolled(event);
		});
		
		dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& event){
			return OnWindowResized(event);
		});
	}
	
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e){
		m_ZoomLevel -= e.GetYOffset() * 0.1f;
		//m_ZoomLevel = (m_ZoomLevel < m_ZoomMin) ? (m_ZoomMin) : m_ZoomLevel;
		//m_ZoomLevel = (m_ZoomLevel > m_ZoomMax) ? (m_ZoomMax) : m_ZoomLevel;
		
		SetProjectionDefault();
		
		return false;
	}
	
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e){
		m_AspectRatio = (float)(e.GetWidth()) / (float)(e.GetHeight());
		//BSE_CORE_INFO("Aspect Ratio: {0}", m_AspectRatio);
		SetAspectRatio(m_AspectRatio);
		// SetProjectionDefault();
		return false;
	}
}
