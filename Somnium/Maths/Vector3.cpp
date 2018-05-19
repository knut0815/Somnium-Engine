#include "Vector3.h"

#include <cmath>

namespace Somnium
{
	namespace Maths
	{
		Vector3  Vector3::operator+ (const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3& Vector3::operator+=(const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		//Subtraction Operator
		Vector3  Vector3::operator- (const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3& Vector3::operator-=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		//Multiplication Operators
		Vector3  Vector3::operator* (const Vector3& rhs) const
		{
			return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
		}

		Vector3& Vector3::operator*=(const Vector3& rhs)
		{
			float x1 = y * rhs.z - z * rhs.y,
			      y1 = z * rhs.x - x * rhs.z,
				  z1 = x * rhs.y - y * rhs.x;

			x = x1; y = y1; z = z1;

			return *this;
		}

		Vector3  Vector3::operator* (float scalar) const
		{
			return Vector3(x * scalar, y * scalar, z * scalar);
		}

		Vector3& Vector3::operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		const double Vector3::Magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}
	}
}