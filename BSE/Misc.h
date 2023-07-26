#ifndef BSE_MISC_H
#define BSE_MISC_H

#include <ProtoCore.h>
// #include <log.h>

// misc useful functions
namespace BSE {
	BSE_API void print_hello(); 
	
	// glm::mat4 One4 = glm::mat4(1.0f);
	// glm::mat4 OneMat4;
	// glm::mat3 OneMat3;
	// glm::vec4 OneVec4;
	// glm::vec3 OneVec3;
	
	// glm::mat4 ZeroMat4;
	// glm::mat3 ZeroMat3;
	// glm::vec4 ZeroVec4;
	// glm::vec3 ZeroVec3;
	
	static glm::mat4 OneMat4 = glm::mat4(1.0f);
	static glm::mat3 OneMat3 = glm::mat3(1.0f);
	static glm::vec4 OneVec4 = glm::vec4(1.0f);
	static glm::vec3 OneVec3 = glm::vec3(1.0f);
	
	static glm::mat4 ZeroMat4 = glm::mat4(0.0f);
	static glm::mat3 ZeroMat3 = glm::mat3(0.0f);
	static glm::vec4 ZeroVec4 = glm::vec4(0.0f);
	static glm::vec3 ZeroVec3 = glm::vec3(0.0f);
}

#endif
