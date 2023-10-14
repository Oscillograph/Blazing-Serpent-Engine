#include <systems/scene/SceneSerializer.h>
// #include <vendor/yaml_cpp/include/yaml-cpp/node/convert.h>

namespace YAML {
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		
		static bool decode(const Node& node, glm::vec3& rhs) {
			if (!node.IsSequence() || (node.size() != 3))
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
	
	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4& rhs) {
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}
		
		static bool decode(const Node& node, glm::vec4& rhs) {
			if (!node.IsSequence() || (node.size() != 4))
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
	
	template<>
	struct convert<glm::mat4> {
		static Node encode(const glm::mat4& rhs) {
			Node node;
			node.push_back(rhs[0][0]);
			node.push_back(rhs[0][1]);
			node.push_back(rhs[0][2]);
			node.push_back(rhs[0][3]);
			node.push_back(rhs[1][0]);
			node.push_back(rhs[1][1]);
			node.push_back(rhs[1][2]);
			node.push_back(rhs[1][3]);
			node.push_back(rhs[2][0]);
			node.push_back(rhs[2][1]);
			node.push_back(rhs[2][2]);
			node.push_back(rhs[2][3]);
			node.push_back(rhs[3][0]);
			node.push_back(rhs[3][1]);
			node.push_back(rhs[3][2]);
			node.push_back(rhs[3][3]);
			return node;
		}
		
		static bool decode(const Node& node, glm::mat4& rhs) {
			if (!node.IsSequence() || (node.size() != 16))
				return false;
			rhs[0][0] = node[0].as<float>();
			rhs[0][1] = node[1].as<float>();
			rhs[0][2] = node[2].as<float>();
			rhs[0][3] = node[3].as<float>();
			rhs[1][0] = node[4].as<float>();
			rhs[1][1] = node[5].as<float>();
			rhs[1][2] = node[6].as<float>();
			rhs[1][3] = node[7].as<float>();
			rhs[2][0] = node[8].as<float>();
			rhs[2][1] = node[9].as<float>();
			rhs[2][2] = node[10].as<float>();
			rhs[2][3] = node[11].as<float>();
			rhs[3][0] = node[12].as<float>();
			rhs[3][1] = node[13].as<float>();
			rhs[3][2] = node[14].as<float>();
			rhs[3][3] = node[15].as<float>();
			return true;
		}
	};
	
	template<>
	struct convert<BSE::OrthographicCameraBounds> {
		static Node encode(const BSE::OrthographicCameraBounds& rhs) {
			Node node;
			node.push_back(rhs.Left);
			node.push_back(rhs.Right);
			node.push_back(rhs.Top);
			node.push_back(rhs.Bottom);
			node.push_back(rhs.ZNear);
			node.push_back(rhs.ZFar);
			return node;
		}
		
		static bool decode(const Node& node, BSE::OrthographicCameraBounds& rhs) {
			if (!node.IsSequence() || (node.size() != 6))
				return false;
			rhs.Left = node[0].as<float>();
			rhs.Right = node[1].as<float>();
			rhs.Top = node[2].as<float>();
			rhs.Bottom = node[3].as<float>();
			rhs.ZNear = node[4].as<float>();
			rhs.ZFar = node[5].as<float>();
			return true;
		}
	};
}

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
		std::string text = FileIO::GetRawText(filename);
		YAML::Node data = YAML::Load(text);
		if (!data["Scene"]){
			return false;
		}
		
		std::string sceneName = data["Scene"].as<std::string>();
		BSE_CORE_INFO("Deserializing scene {0}", sceneName.c_str());
		
		auto entities = data["Entities"];
		if (entities) {
			for (auto entity : entities) {
				uint32_t entityId = entity["Entity"].as<uint32_t>(); // TODO: implement entity id restoration
				
				std::string name;
				auto nameNode = entity["NameComponent"];
				if (nameNode)
					name = nameNode["Name"].as<std::string>();
				
				BSE_CORE_INFO("Deserializing entity with id = {0}, name = {1}", entityId, name);
				
				Entity deserializedEntity = *(m_SceneContext->CreateEntity(name));
				
				auto transformNode = entity["TransformComponent"];
				if (transformNode){
					auto& transform = deserializedEntity.GetComponent<TransformComponent>();
					transform.Translation = transformNode["Translation"].as<glm::vec3>();
					transform.Rotation = transformNode["Rotation"].as<glm::vec3>();
					transform.Scale = transformNode["Scale"].as<glm::vec3>();
				}
				
				auto idNode = entity["UUIDComponent"];
				if (idNode){
					uint64_t uuid;
					uuid = nameNode["UUID"].as<uint64_t>();
					auto& idComponent = deserializedEntity.AddComponent<UUIDComponent>(uuid);
				}

				auto cameraControllerComponentNode = entity["CameraControllerComponent"];
				if (cameraControllerComponentNode){
					bool playerControlled = cameraControllerComponentNode["Player Controlled"].as<bool>();
					bool works = cameraControllerComponentNode["Works"].as<bool>();
					
					auto cameraControllerNode = cameraControllerComponentNode["CameraController"];
					if (cameraControllerNode){
						bool editorCamera = cameraControllerNode["EditorCamera"].as<bool>();
						float aspectRatio = cameraControllerNode["AspectRatio"].as<float>();
						float zoomLevel = cameraControllerNode["ZoomLevel"].as<float>();
						bool allowRotation = cameraControllerNode["Rotatable"].as<bool>();
						bool allowTranslation = cameraControllerNode["Translatable"].as<bool>();
						bool allowZoom = cameraControllerNode["Zoomable"].as<bool>();
						bool constantAspectRatio = cameraControllerNode["ConstantAspectRatio"].as<bool>();
						
						
						auto& component = deserializedEntity.AddComponent<CameraControllerComponent>(aspectRatio, zoomLevel, allowRotation, constantAspectRatio);
						component.PlayerControlled = playerControlled;
						component.Works = works;
						
						CameraController* controller = component.cameraController;
						m_SceneContext->SetCameraController(controller);
						controller->SetProjectionType((CameraProjectionType)cameraControllerNode["ProjectionType"].as<int>());
						if (controller->GetProjectionType() == CameraProjectionType::Perspective){
							controller->SetPerspectiveFOV(cameraControllerNode["PerspectiveFOV"].as<float>());
							// controller->SetPerspectiveVerticalFOV(cameraControllerNode["PerspectiveVerticalFOV"].as<float>());
							controller->SetPerspectiveNear(cameraControllerNode["PerspectiveNear"].as<float>());
							controller->SetPerspectiveFar(cameraControllerNode["PerspectiveFar"].as<float>());
						}
						controller->editorCamera = editorCamera;
						controller->allowTranslation = allowTranslation;
						controller->allowRotation = allowRotation;
						controller->allowZoom = allowZoom;
						controller->constantAspectRatio = constantAspectRatio;
						
						if (editorCamera)
							m_SceneContext->SetCameraController(controller);
						
						auto cameraNode = cameraControllerNode["Camera"];
						if (cameraNode){
							GeneralCamera* camera = controller->GetCamera();
							camera->SetProjection(cameraNode["ProjectionMatrix"].as<glm::mat4>());
							// camera->SetProjection(cameraNode["ViewMatrix"].as<glm::mat4>());
							controller->SetCameraPosition(cameraNode["Position"].as<glm::vec3>());
							controller->Rotate(cameraNode["Rotation"].as<glm::vec3>());
							controller->UpdateView();
							// camera = nullptr;
						}
						controller = nullptr;
					}
				}
				
				auto spriteNode = entity["SpriteComponent"];
				if (spriteNode){
					auto& sprite = deserializedEntity.AddComponent<SpriteComponent>();
					sprite.Color = spriteNode["Color"].as<glm::vec4>();
				}
			}
		}
		m_SceneContext->GetCameraController()->OnUpdate(0.0f);
		BSE_CORE_INFO("Deserialization complete, camera controller updated");

		return true;
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
				out << YAML::Key << "TransformComponent";
				out << YAML::BeginMap;
					auto& transform = entity.GetComponent<TransformComponent>();
					out << YAML::Key << "Translation" << YAML::Value << transform.Translation;
					out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
					out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
				out << YAML::EndMap;
			}
			
			if (entity.HasComponent<UUIDComponent>()){
				out << YAML::Key << "UUIDComponent";
				out << YAML::BeginMap;
					auto& idComponent = entity.GetComponent<UUIDComponent>();
					out << YAML::Key << "UUID" << YAML::Value << idComponent.ID;
				out << YAML::EndMap;
			}
		
			if (entity.HasComponent<CameraControllerComponent>()){
				auto& component = entity.GetComponent<CameraControllerComponent>();
				out << YAML::Key << "CameraControllerComponent";
				out << YAML::BeginMap;
					out << YAML::Key << "Player Controlled" << YAML::Value << component.PlayerControlled;
					out << YAML::Key << "Works" << YAML::Value << component.Works;
					
					auto& cameraController = component.cameraController;
					out << YAML::Key << "CameraController" << YAML::Value;
					out << YAML::BeginMap;
						out << YAML::Key << "EditorCamera" << YAML::Value << cameraController->editorCamera;
						out << YAML::Key << "Rotatable" << YAML::Value << cameraController->allowRotation;
						out << YAML::Key << "Translatable" << YAML::Value << cameraController->allowTranslation;
						out << YAML::Key << "Zoomable" << YAML::Value << cameraController->allowZoom;
						out << YAML::Key << "ConstantAspectRatio" << YAML::Value << cameraController->constantAspectRatio;
						out << YAML::Key << "ProjectionType" << YAML::Value << (int)cameraController->GetProjectionType();
						if (cameraController->GetProjectionType() == CameraProjectionType::Perspective){
							// out << YAML::Key << "PerspectiveHorizontalFOV" << YAML::Value << cameraController->GetPerspectiveHorizontalFOV();
							out << YAML::Key << "PerspectiveFOV" << YAML::Value << cameraController->GetPerspectiveFOV();
							out << YAML::Key << "PerspectiveNear" << YAML::Value << cameraController->GetPerspectiveNear();
							out << YAML::Key << "PerspectiveFar" << YAML::Value << cameraController->GetPerspectiveFar();
						}
				
						out << YAML::Key << "OrthographicCameraBounds" << YAML::Value << cameraController->GetBounds();
						out << YAML::Key << "AspectRatio" << YAML::Value << cameraController->GetAspectRatio();
						out << YAML::Key << "ZoomLevel" << YAML::Value << cameraController->GetZoomLevel();
						
						auto camera = cameraController->GetCamera();
						out << YAML::Key << "Camera" << YAML::Value;
						out << YAML::BeginMap;
							out << YAML::Key << "ProjectionMatrix" << YAML::Value << camera->GetProjectionMatrix();
							out << YAML::Key << "ViewMatrix" << YAML::Value << camera->GetViewMatrix();
							out << YAML::Key << "ViewProjectionMatrix" << YAML::Value << camera->GetViewProjectionMatrix();
							out << YAML::Key << "Position" << YAML::Value << camera->GetPosition();
							out << YAML::Key << "Rotation" << YAML::Value << camera->GetRotation();
							out << YAML::Key << "RotationX" << YAML::Value << camera->GetPitch();
							out << YAML::Key << "RotationY" << YAML::Value << camera->GetYaw();
							out << YAML::Key << "RotationZ" << YAML::Value << camera->GetRoll();
						out << YAML::EndMap;
					out << YAML::EndMap;
				out << YAML::EndMap;
			}
			
			if (entity.HasComponent<SpriteComponent>()){
				out << YAML::Key << "SpriteComponent";
				out << YAML::BeginMap;
					auto& component = entity.GetComponent<SpriteComponent>();
					out << YAML::Key << "Color" << YAML::Value << component.Color;
				out << YAML::EndMap;
			}
		out << YAML::EndMap;
		return false;
	}
}
