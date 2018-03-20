#pragma once

namespace LKREngine
{
	namespace Maths
	{
		struct Vector4
		{
			float x, y, z, w;
			
			Vector4() = default;

			Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
				: x(x), y(y), z(z), w(w) {};
			
			~Vector4() {};

			//Addition Operators
			Vector4  operator+ (const Vector4&) const;
			Vector4& operator+=(const Vector4&);

			//Subtraction Operators
			Vector4  operator- (const Vector4&) const;
			Vector4& operator-=(const Vector4&);

			//Multiplication Operators
			Vector4  operator* (float) const;
			Vector4& operator*=(float);

			const double Magnitude(void) const;
		};
	}
}