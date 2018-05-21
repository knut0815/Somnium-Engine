#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>

#include "../Utilities/FileUtilities.h"

using namespace std;
using namespace Somnium;
using namespace Utilities;
using namespace Maths;

namespace Somnium {
	namespace Graphics {

		Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
			:m_VertexFilePath(vertexFilePath), m_FragmentFilePath(fragmentFilePath)
		{
			m_ShaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		GLuint Shader::load() 
		{
			GLint  result;
			GLuint program			= glCreateProgram();
			GLuint vertexShader		= glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShader	= glCreateShader(GL_FRAGMENT_SHADER);
			
			string vertexSource		= readFile(m_VertexFilePath);
			string fragmentSource	= readFile(m_FragmentFilePath);

			GLuint shaders[2]		= { vertexShader, fragmentShader };
			
			if (vertexSource.empty() || fragmentSource.empty())
				return 0;

			const char * const vs	= vertexSource.c_str();
			const char * const fs	= fragmentSource.c_str();
			
			const char * const *sources[2]	= { &vs, &fs };

			for (int i = 0; i < 2; i++)
			{
				glShaderSource(shaders[i], 1, sources[i], NULL);
				glCompileShader(shaders[i]);

				glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &result);

				if (!result)
				{
					GLint length;
					glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &length);
					vector<char> error(length);
					glGetShaderInfoLog(shaders[i], length, &length, &error[0]);
					cerr << &error[0] << endl;
					glDeleteShader(shaders[i]);

					return 0;
				}
			}

			for (int i = 0; i < 2; i++) 
				glAttachShader(program, shaders[i]);
			
			glLinkProgram(program);
			glValidateProgram(program);
			glUseProgram(program);
			
			for (int i = 0; i < 2; i++)
				glDeleteShader(shaders[i]);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniform(const GLchar* name, int value) 
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform(const GLchar* name, const Vector2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform(const GLchar* name, const Vector3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform(const GLchar* name, const Vector4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniform(const GLchar* name, const Matrix4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::enable() const 
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}
	}
}