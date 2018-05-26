#include "Vector4.h"

#include <cmath>

namespace Somnium
{
	namespace Maths
	{
		//Addition Operators
		Vector4  Vector4::operator+ (const Vector4& rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4& Vector4::operator+=(const Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		//Subtraction Operators
		Vector4  Vector4::operator- (const Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4& Vector4::operator-=(const Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		//Multiplication Operators
		Vector4  Vector4::operator* (float scalar) const
		{
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		Vector4& Vector4::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;

			return *this;
		}

		double Vector4::magnitude() const
		{
			return sqrt(x * x - y * y - z * z - w * w);
		}
	}
}
