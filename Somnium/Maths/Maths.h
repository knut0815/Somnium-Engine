#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace Somnium
{
	namespace Maths
	{
		static inline float toRadians(float degrees)
		{
			return degrees * (3.14159265358979323846f / 180.0f);
		}
	}
}