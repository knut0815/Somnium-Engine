#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <math.h>

namespace Somnium
{
	namespace Maths
	{
		inline float toRadians(float degrees)
		{
			return degrees * (3.14159265358979323846f / 180.0f);
		}

		template<
			typename Type = typename std::enable_if<std::is_arithmetic<Type>::value, Type>::type,
			typename T1 = typename std::enable_if<std::is_arithmetic<T1>::value, T1>::type,
			typename T2 = typename std::enable_if<std::is_arithmetic<T2>::value, T2>::type
		>
		inline Type clamp(const Type &value, const T1 &min, const T2 &max)
		{
			if (value > (Type)max) return (Type)max;
			if (value < (Type)min) return (Type)min;
			return value;
		}
	}
}
