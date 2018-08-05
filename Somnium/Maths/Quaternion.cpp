#include "Quaternion.h"

namespace Somnium
{
	namespace Maths
	{
		Quaternion& Quaternion::operator+=(const Quaternion &rhs)
		{
			data.vw += rhs.data.vw;
			return *this;
		}

		Quaternion& Quaternion::operator-=(const Quaternion &rhs)
		{
			data.vw -= rhs.data.vw;
			return *this;
		}

		inline float Quaternion::dot(const Quaternion &quaternion)
		{
			return dot(*this, quaternion);
		}

		inline float dot(const Quaternion &quaternion1, const Quaternion &quaternion2)
		{
			return Vector3::dot(quaternion1.data.v, quaternion2.data.v) + quaternion1.data.w * quaternion2.data.w;
		}

		inline Quaternion Quaternion::normalise(const Quaternion &quaternion)
		{
			return Quaternion(quaternion.data.vw / (float)sqrt(dot(quaternion, quaternion)));
		}
	}
}