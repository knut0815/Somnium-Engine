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

			static Matrix4 Identity();
			static Matrix4 Orthographic(float, float, float, float, float, float);
			static Matrix4 Perspective (float, float, float, float);

			static Matrix4 Translation(const Vector3&);
			static Matrix4 Rotation(float, const Vector3&);
			static Matrix4 Scale(const Vector3&);

			union
			{
				float elements  [4 * 4] = { 0 };
				float elements2D[4] [4];
				Vector4 columns [4];
			};
		};
	}
}