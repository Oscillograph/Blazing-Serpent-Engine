#include <systems/OrthographicCameraController.h>

namespace BSE {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float zoomLevel, bool rotation){
		//BSE_CORE_TRACE("Calling Camera Controller constructor");
		m_AspectRatio = aspectRatio;
		m_AspectRatioPrev = m_AspectRatio;
		m_ZoomLevel = zoomLevel;
		m_Rotation = rotation;
		
		m_Camera = new OrthographicCamera(
			-m_AspectRatio * m_ZoomLevel,
			 m_AspectRatio * m_ZoomLevel,
			 m_ZoomLevel,
			-m_ZoomLevel
			);
		
		m_CameraPosition = m_Camera->GetPosition();
		
		// m_WidthPrev = Application::Get()->GetWindow()->GetWidth();
		// m_HeightPrev = Application::Get()->GetWindow()->GetHeight();
		//BSE_CORE_TRACE("Camera Controller constructor out");
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
		float widthNew = (float)(e.GetWidth());
		float heightNew = (float)(e.GetHeight());
		
		/*
		if ((m_HeightPrev > 0.0f) || (m_WidthPrev > 0.0f)){
			float zoomAdjust = (widthNew * heightNew) / (m_HeightPrev * m_WidthPrev);
			m_ZoomLevel *= zoomAdjust;
		}
		*/
		
		m_AspectRatio = widthNew / heightNew;
		m_ZoomLevel = m_ZoomLevel * m_AspectRatio / m_AspectRatioPrev;
		
		m_AspectRatioPrev = m_AspectRatio;
		m_HeightPrev = widthNew;
		m_WidthPrev = heightNew;
		
		// SetAspectRatio(m_AspectRatio);
		SetProjectionDefault();
		return false;
	}
}
