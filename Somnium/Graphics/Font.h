#pragma once

#include "../Maths/Vector2.h"
#include <glew.h>
#include <glfw3.h>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Somnium
{
	namespace Graphics
	{
		struct UICharacter
		{
			GLuint m_TextureID;
			Maths::Vector2 m_Size;
			Maths::Vector2 m_Bearing;
			GLuint m_Advance;
		};

		class Font
		{
		public:
			Font(const char* fontFilepath, const FT_Library& freeTypeInstance);
			~Font();

		private:
			const FT_Library& m_FreeType;
			FT_GlyphSlot m_GlyphSlot;
			FT_Face m_Face;
			std::map<GLchar, UICharacter> m_CharacterMap;
		};
	}
}