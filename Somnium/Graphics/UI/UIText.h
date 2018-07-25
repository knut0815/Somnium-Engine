#pragma once

#include "UIObject.h"
#include "../Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace Somnium
{
	namespace Graphics
	{
		namespace UI
		{
			class UIText : public UIObject
			{
			public:
				UIText() {};
				UIText(Font* font, char *text, unsigned int& size) {};
				~UIText() {};

				void setText(char *text) { m_Text = text; };
				void setFont(Font* font) { m_Font = font; };
				void setSize(char *fontFilepath) {};
				
				void setItalic(bool italic) {};
				void setBold(bool bold) {};

			private:
				bool m_Italic = false, m_Bold = false;
				Font *m_Font;
				char *m_Text;
			};
		}
	}
}