#pragma once

namespace Somnium
{
	namespace Maths
	{
		struct Vector3
		{
			float x, y, z;

			Vector3(float x = 0, float y = 0, float z = 0)
				: x(x), y(y), z(z) {};

			~Vector3() {};

			//Addition Operators
			Vector3  operator+ (const Vector3&) const;
			Vector3& operator+=(const Vector3&);

			//Negation operator
			Vector3 operator-() const;

			//Subtraction Operators
			Vector3  operator- (const Vector3&) const;
			Vector3& operator-=(const Vector3&);

			//Multiplication Operators
			Vector3  operator* (const Vector3&) const;
			Vector3& operator*=(const Vector3&);

			Vector3  operator* (float) const;
			Vector3& operator*=(float);

			Vector3 normalise() const;
			float dot(const Vector3 &vector) const;

			double magnitude(void) const;
		};
	}
}
