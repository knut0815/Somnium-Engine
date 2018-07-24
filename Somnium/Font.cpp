#include "Font.h"
#include <iostream>

namespace Somnium
{
	namespace Graphics
	{
		Font::Font(std::string fontFilepath)
		{
			const int status = FT_New_Face(m_FreeType, fontFilepath.c_str(), 0, &m_Face);
			switch (status)
			{
			case FT_Err_Unknown_File_Format:
				std::cerr << "ERROR: FreeType font not recognised" << std::endl;
				break;
			default:
				std::cerr << "ERROR: FreeType Failed to load font (Error Code: " << status << ")" << std::endl;
				break;
			case 0:
				FT_Set_Pixel_Sizes(m_Face, 0, 48);
				if (FT_Load_Char(m_Face, 'X', FT_LOAD_RENDER)) std::cerr << "ERROR: Failed to load Glyph" << std::endl;
				else
					m_GlyphSlot = m_Face->glyph;
				break;
			}
		}
	}
}