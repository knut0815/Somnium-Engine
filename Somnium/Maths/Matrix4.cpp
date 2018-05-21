#include "Matrix4.h"

#include <iostream>

namespace Somnium
{
	namespace Maths
	{
		Matrix4::Matrix4()
		{
		
		}

		Matrix4::Matrix4(float diagonal)
		{
			for (int i = 0; i < 4; i++)
				elements2D[i][i] = diagonal;
		}

		Matrix4::~Matrix4() 
		{

		}

		Matrix4& Matrix4::operator=(const Matrix4& rhs)
		{
			for (int i = 0; i < 16; i++)
				elements[i] = rhs.elements[i];

			return *this;
		}

		Matrix4::Matrix4(const Matrix4& rhs)
		{
			for (int i = 0; i < 16; i++)
				elements[i] = rhs.elements[i];
		}

		Matrix4& Matrix4::operator+=(const Matrix4& rhs)
		{
			for (int i = 0; i < 16; i++)
				elements[i] += rhs.elements[i];

			return *this;
		}

		Matrix4& Matrix4::operator-=(const Matrix4& rhs)
		{
			for (int i = 0; i < 16; i++)
				elements[i] -= rhs.elements[i];

			return *this;
		}

		Matrix4& Matrix4::operator*=(const Matrix4& rhs)
		{
			Matrix4 temp;

			for (int r = 0; r < 4; r++)
				for (int c = 0; c < 4; c++)
					for(int e = 0; e < 4; e++)
						temp.elements2D[r][c] += elements2D[r][e] * rhs.elements2D[e][c];

			*this = temp;

			return *this;
		}

		Matrix4& Matrix4::operator+=(const int& scalar)
		{
			for (int i = 0; i < 16; i++)
				elements[i] += scalar;

			return *this;
		}

		Matrix4& Matrix4::operator-=(const int& scalar)
		{
			for (int i = 0; i < 16; i++)
				elements[i] -= scalar;

			return *this;
		}

		Matrix4& Matrix4::operator*=(const int& scalar)
		{
			for (int i = 0; i < 16; i++)
				elements[i] *= scalar;

			return *this;
		}

		Matrix4& Matrix4::operator/=(const int& scalar)
		{
			for (int i = 0; i < 16; i++)
				elements[i] /= scalar;

			return *this;
		}

		Matrix4 operator+ (const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = lhs.elements[i] + rhs.elements[i];

			return temp;
		}

		Matrix4 operator- (const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = lhs.elements[i] - rhs.elements[i];

			return temp;
		}

		Matrix4 operator* (const Matrix4& lhs, const Matrix4& rhs)
		{
			Matrix4 temp;

			for (int r = 0; r < 4; r++)
				for (int c = 0; c < 4; c++)
					for (int e = 0; e < 4; e++)
						temp.elements2D[r][c] += lhs.elements2D[r][e] * rhs.elements2D[e][c];

			return temp;
		}

		Matrix4 operator+(const Matrix4& matrix, const int& scalar)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = matrix.elements[i] + scalar;

			return temp;
		}

		Matrix4 operator-(const Matrix4& matrix, const int& scalar)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = matrix.elements[i] - scalar;

			return temp;
		}

		Matrix4 operator*(const Matrix4& matrix, const int& scalar)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = matrix.elements[i] * scalar;

			return temp;
		}

		Matrix4 operator/(const Matrix4& matrix, const int& scalar)
		{
			Matrix4 temp;

			for (int i = 0; i < 16; i++)
				temp.elements[i] = matrix.elements[i] / scalar;

			return temp;
		}


		Matrix4 Matrix4::identity()
		{
			return Matrix4(1);
		}

		Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4 orthographic(1.0f);
			
			orthographic.elements2D[0][0] = 2.0f / (right - left);
			orthographic.elements2D[1][1] = 2.0f / (top - bottom);
			orthographic.elements2D[2][2] = -2.0f / (far - near);
			orthographic.elements2D[3][0] = -((right + left) / (right - left));
			orthographic.elements2D[3][1] = -((top + bottom) / (top - bottom));
			orthographic.elements2D[3][2] = -((far + near) / (far - near));

			return orthographic;
		}

		Matrix4 Matrix4::perspective(float fieldOfView, float aspectRatio, float near, float far)
		{
			Matrix4 perspective(1);

			float q = 1.0f / tan(toRadians(0.5f * fieldOfView)),
				  a = q / aspectRatio,
				  b = (near + far) / (near - far),
				  c = (2.0f * near * far) / (near - far);

			perspective.elements2D[0][0] = a;
			perspective.elements2D[1][1] = q;
			perspective.elements2D[2][2] = b;
			perspective.elements[14] = -1.0f;
			perspective.elements[11] = c;

			return perspective;
		}

		Matrix4 Matrix4::translation(const Vector3& translation)
		{
			Matrix4 translationMatrix(1);

			translationMatrix.elements2D[3][0] = translation.x;
			translationMatrix.elements2D[3][1] = translation.y;
			translationMatrix.elements2D[3][2] = translation.z;

			return translationMatrix;
		}

		Matrix4 Matrix4::rotation(float angle, const Vector3& axis)
		{
			Matrix4 rotationMatrix(1);
			float r = toRadians(angle),
				  c = cos(r),
				  s = sin(r),
				  omc = 1.0f - c;
				  
			const float& x = axis.x,
				         y = axis.y,
				         z = axis.z;

			rotationMatrix.elements2D[0][0] = x * omc + c;
			rotationMatrix.elements[4] = y * x * omc + z * s;
			rotationMatrix.elements[8] = x * z * omc - y * s;
			rotationMatrix.elements[1] = x * y * omc - z * s;
			rotationMatrix.elements[5] = y * y * omc + c;
			rotationMatrix.elements[9] = y * z * omc + x * s;
			rotationMatrix.elements[2] = x * z * omc + y * s;
			rotationMatrix.elements[6] = y * z * omc - x * s;
			rotationMatrix.elements[10] = z * z * omc + c;

			return rotationMatrix;
		}

		Matrix4 Matrix4::scale(const Vector3& scale)
		{
			Matrix4 scaleMatrix(1);

			scaleMatrix.elements2D[0][0] = scale.x;
			scaleMatrix.elements2D[1][1] = scale.y;
			scaleMatrix.elements2D[2][2] = scale.z;

			return scaleMatrix;
		}
	}
}