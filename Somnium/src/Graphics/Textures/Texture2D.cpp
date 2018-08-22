#include "Texture2D.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace Textures
		{
			Texture2D::Texture2D() {
					glGenTextures(1, &m_TextureID);

					bind();

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

					unbind();
			}

			Texture2D::~Texture2D() {

			}
		}
	}
}
