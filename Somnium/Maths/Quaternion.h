#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

namespace Somnium
{
	namespace Maths
	{
		struct Quaternion
		{
		public :
			union Data{
				Vector4 vw = Vector4();
				struct {
					Vector3 v;
					float w;
				};

				Data() { vw = Vector4(); }
				~Data() {};
			} data;

			Quaternion(float x, float y, float z, float w)
			{
				data.vw = Vector4(x, y, z, w);
			}

			Quaternion(Vector3 v, float w)
			{
				data.v = v;
				data.w = w;
			}

			Quaternion(Vector4 vw)
			{
				data.vw = vw;
			}

			Quaternion &operator+=(const Quaternion &rhs);
			Quaternion &operator-=(const Quaternion &rhs);

			inline float dot(const Quaternion &quaternion);
			static inline float dot(const Quaternion &quaternion1, const Quaternion &quaternion2);

			inline Quaternion normalise(const Quaternion &quaternion);
		};
	}
}