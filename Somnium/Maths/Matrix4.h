#pragma once

#include "Maths.h"

namespace Somnium
{
	namespace Maths
	{
		struct Matrix4 {
			Matrix4();
			Matrix4(float);
			Matrix4(const Matrix4&);

			~Matrix4();

			Matrix4& operator=(const Matrix4&);

			Matrix4& operator+=(const Matrix4&);
			Matrix4& operator-=(const Matrix4&);
			Matrix4& operator*=(const Matrix4&);

			Matrix4& operator+=(const int&);
			Matrix4& operator-=(const int&);
			Matrix4& operator*=(const int&);
			Matrix4& operator/=(const int&);

			friend Matrix4 operator+(const Matrix4&, const Matrix4&);
			friend Matrix4 operator-(const Matrix4&, const Matrix4&);
			friend Matrix4 operator*(const Matrix4&, const Matrix4&);
		
			friend Matrix4 operator+(const Matrix4&, const int&);
			friend Matrix4 operator-(const Matrix4&, const int&);
			friend Matrix4 operator*(const Matrix4&, const int&);
			friend Matrix4 operator/(const Matrix4&, const int&);

			static Matrix4 identity();
			static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix4 perspective (float fieldOfView, float aspectRatio, float near, float far);

			static Matrix4 translation(const Vector3&);
			static Matrix4 rotation(float, const Vector3&);
			static Matrix4 scale(const Vector3&);

			union
			{
				float elements  [4 * 4] = { 0 };
				float elements2D[4] [4];
				Vector4 columns [4];
			};
		};
	}
}