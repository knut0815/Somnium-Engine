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

			void setUniform(const GLchar*, int value);
			void setUniform(const GLchar*, float value);
			void setUniform(const GLchar*, const Maths::Vector2&);
			void setUniform(const GLchar*, const Maths::Vector3&);
			void setUniform(const GLchar*, const Maths::Vector4&);
			void setUniform(const GLchar*, const Maths::Matrix4&);

			void enable() const;
			void disable() const;

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar*);

		private:
			GLuint m_ShaderID;
			const char *m_VertexFilePath, *m_FragmentFilePath;
		};
	}
}