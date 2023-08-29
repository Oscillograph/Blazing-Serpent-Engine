#include <systems/scene/SceneSerializer.h>

namespace BSE {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& vec3){
		out << YAML::Flow;
		out << YAML::BeginSeq << vec3.x << vec3.y << vec3.z << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& vec4){
		out << YAML::Flow;
		out << YAML::BeginSeq << vec4.x << vec4.y << vec4.z << vec4.w << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::mat4& mat4){
		out << YAML::Flow;
		out << YAML::BeginSeq;
			out << mat4[0][0] << mat4[0][1] << mat4[0][2] << mat4[0][3];
			out << mat4[1][0] << mat4[1][1] << mat4[1][2] << mat4[1][3];
			out << mat4[2][0] << mat4[2][1] << mat4[2][2] << mat4[2][3];
			out << mat4[3][0] << mat4[3][1] << mat4[3][2] << mat4[3][3];
		out << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const OrthographicCameraBounds& bounds){
		out << YAML::Flow;
		out << YAML::BeginSeq;
			out << bounds.Left << bounds.Right;
			out << bounds.Top << bounds.Bottom;
			out << bounds.ZNear << bounds.ZFar; 
		out << YAML::EndSeq;
		return out;
	}
	
	
	SceneSerializer::SceneSerializer(Scene* scene){
		m_SceneContext = scene;
	}
	SceneSerializer::~SceneSerializer(){
		m_SceneContext = nullptr;
	}
	
	bool SceneSerializer::Serialize(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::SerializeToFile(const std::string& filename){
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Unnamed";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_SceneContext->Registry().each([&](auto entityID){
			Entity entity = {entityID, m_SceneContext};
			if (!entity)
				return;
			SerializeEntity(out, entity);
		});
		
		out << YAML::EndSeq;
		out << YAML::EndMap;
		
		return FileIO::WriteRawText(filename, out.c_str());
	}
	
	bool SceneSerializer::SerializeRuntime(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::Deserialize(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::DeserializeFromFile(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::DeserializeRuntime(const std::string& filename){
		// Not implemented yet
		BSE_CORE_ASSERT(false);
		return false;
	}
	
	bool SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity& entity){
		out << YAML::BeginMap;
			out << YAML::Key << "Entity" << YAML::Value << (uint32_t)entity.GetID();
			
			if (entity.HasComponent<NameComponent>()){
				out << YAML::Key << "NameComponent";
				out << YAML::BeginMap;
					auto& name = entity.GetComponent<NameComponent>().Name;
					out << YAML::Key << "Name" << YAML::Value << name;
				out << YAML::EndMap;
			}
			
			if (entity.HasComponent<TransformComponent>()){
				out << YAML::Key << "NameComponent";
				out << YAML::BeginMap;
					auto& transform = entity.GetComponent<TransformComponent>();
					out << YAML::Key << "Translation" << YAML::Value << transform.Translation;
					out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
					out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
				out << YAML::EndMap;
			}
			
			if (entity.HasComponent<CameraControllerComponent>()){
				auto& component = entity.GetComponent<CameraControllerComponent>();
				out << YAML::Key << "CameraControllerComponent";
				out << YAML::BeginMap;
					out << YAML::Key << "Player Controlled" << YAML::Value << component.PlayerControlled;
					out << YAML::Key << "Works" << YAML::Value << component.Works;
					
					auto& cameraController = component.CameraController;
					out << YAML::Key << "CameraController" << YAML::Value;
					out << YAML::BeginMap;
						out << YAML::Key << "Rotatable" << YAML::Value << cameraController->RotationStatus();
						out << YAML::Key << "ConstantAspectRatio" << YAML::Value << cameraController->GetConstantAspectRatio();
						out << YAML::Key << "ProjectionType" << YAML::Value << (int)cameraController->GetProjectionType();
						if (cameraController->GetProjectionType() == CameraProjectionType::Perspective){
							out << YAML::Key << "PerspectiveHorizontalFOV" << YAML::Value << cameraController->GetPerspectiveHorizontalFOV();
							out << YAML::Key << "PerspectiveVerticalFOV" << YAML::Value << cameraController->GetPerspectiveVerticalFOV();
							out << YAML::Key << "PerspectiveNear" << YAML::Value << cameraController->GetPerspectiveNear();
							out << YAML::Key << "PerspectiveFar" << YAML::Value << cameraController->GetPerspectiveFar();
						}
						if (cameraController->GetProjectionType() == CameraProjectionType::Orthographic){
							out << YAML::Key << "OrthographicCameraBounds" << cameraController->GetBounds();
							out << YAML::Key << "AspectRatio" << cameraController->GetAspectRatio();
							out << YAML::Key << "ZoomLevel" << cameraController->GetZoomLevel();
						}
				
						auto camera = cameraController->GetCamera();
						out << YAML::Key << "Camera" << YAML::Value;
						out << YAML::BeginMap;
							out << YAML::Key << "ProjectionMatrix" << YAML::Value << camera->GetProjectionMatrix();
							out << YAML::Key << "ViewMatrix" << YAML::Value << camera->GetViewMatrix();
							out << YAML::Key << "ViewProjectionMatrix" << YAML::Value << camera->GetViewProjectionMatrix();
							out << YAML::Key << "Position" << YAML::Value << camera->GetPosition();
							out << YAML::Key << "Rotation" << YAML::Value << camera->GetRotation();
							out << YAML::Key << "RotationX" << YAML::Value << camera->GetRotationX();
							out << YAML::Key << "RotationY" << YAML::Value << camera->GetRotationY();
							out << YAML::Key << "RotationZ" << YAML::Value << camera->GetRotationZ();
						out << YAML::EndMap;
					out << YAML::EndMap;
				out << YAML::EndMap;
			}
		
			if (entity.HasComponent<SpriteComponent>()){
				out << YAML::Key << "SpriteComponent";
				out << YAML::BeginMap;
					auto& component = entity.GetComponent<SpriteComponent>();
					out << YAML::Key << "Name" << YAML::Value << component.Color;
				out << YAML::EndMap;
			}
		out << YAML::EndMap;
		
		return false;
	}
}
