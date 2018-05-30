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

			void setInt(const GLchar*, int value);
			void setFloat(const GLchar*, float value);
			void setVector2(const GLchar*, const Maths::Vector2&);
			void setVector3(const GLchar*, const Maths::Vector3&);
			void setVector4(const GLchar*, const Maths::Vector4&);
			void setMatrix4(const GLchar*, const Maths::Matrix4&);

			void enable() const;
			void disable() const;

            const GLuint getID() const { return m_ShaderID; };

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar*);

		private:
			GLuint m_ShaderID;
			const char *m_VertexFilePath, *m_FragmentFilePath;
		};
	}
}
