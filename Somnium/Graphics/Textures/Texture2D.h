#pragma once

#ifdef WEB_BUILD
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <glew.h>
#endif

namespace Somnium
{
	namespace Graphics
	{
		namespace Textures
		{
			class Texture2D
			{
				public:
					Texture2D();
					virtual ~Texture2D();

					inline void bind() const { glBindTexture(GL_TEXTURE_2D, m_TextureID); }
					inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

				private:
					GLuint m_TextureID = 0;
			};
		}
	}
}
