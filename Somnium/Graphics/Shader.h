#pragma once

#include <glew.h>
#include "../Maths/Maths.h"

namespace Somnium {
	namespace Graphics {
		class Shader
		{
		public:
			Shader(const char* vertexFilePath, const char* fragmentFilePath);
			~Shader();

			void SetUniform(const GLchar*, int value);
			void SetUniform(const GLchar*, float value);
			void SetUniform(const GLchar*, const Maths::Vector2&);
			void SetUniform(const GLchar*, const Maths::Vector3&);
			void SetUniform(const GLchar*, const Maths::Vector4&);
			void SetUniform(const GLchar*, const Maths::Matrix4&);

			void Enable() const;
			void Disable() const;

		private:
			GLuint Load();
			GLint GetUniformLocation(const GLchar*);

		private:
			GLuint m_ShaderID;
			const char *m_VertexFilePath, *m_FragmentFilePath;
		};
	}
}