#include "Font.h"
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		Font::Font(const char* fontFilepath, const FT_Library& freeTypeInstance)
			: m_FreeType(freeTypeInstance)
		{
			const int status = FT_New_Face(m_FreeType, fontFilepath, 0, &m_Face);
			
			if (status)
			{
				if(status == FT_Err_Unknown_File_Format)
					std::cerr << "ERROR: FreeType font not recognised" << std::endl;
				else
					std::cerr << "ERROR: FreeType Failed to load font (Error Code: " << status << ")" << std::endl;
				return;
			}
			
			FT_Set_Pixel_Sizes(m_Face, 0, 48);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (GLubyte c = 0; c < 128; c++)
			{
				if(FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
				{
					std::cerr << "ERROR: Failed to load Glyph '" << (char) c << "'" << std::endl;
					continue;
				}

				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					m_Face->glyph->bitmap.width,
					m_Face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					m_Face->glyph->bitmap.buffer
				);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				UICharacter uiChar = {
					tex,
					Maths::Vector2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
					Maths::Vector2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
					m_Face->glyph->advance.x
				};

				m_CharacterMap.insert(std::pair<GLchar, UICharacter>(c, uiChar));
			}

			glBindTexture(GL_TEXTURE_2D, 0);

			FT_Done_Face(m_Face);
			//FT_Done_FreeType(m_FreeType);
		}
	}
}
