#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Somnium
{
	namespace Graphics
	{
		class Font
		{
		public:
			Font(const char* fontFilepath, const FT_Library& freeTypeInstance);
			~Font();

		private:
			const FT_Library& m_FreeType;
			FT_GlyphSlot m_GlyphSlot;
			FT_Face m_Face;
		};
	}
}