#ifndef BSE_MATH_H
#define BSE_MATH_H

#include <ProtoCore.h>

namespace BSE {
	namespace Math {
		// from glm/glx/matrix_decompose.inl
		using T = float;
		using namespace glm;
		
		bool BSE_API Mat4Decompose(const mat4& ModelMatrix, vec3& Translation, vec3& Rotation, vec3& Scale);
	}
}

#endif
