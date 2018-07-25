#pragma once

#include "UIObject.h"
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
				~UIText() {};

				void setText(char *text) { m_Text = text; };
				void setFont(char *fontFilepath) {};
				void setSize(char *fontFilepath) {};
				
				void setItalic(bool italic) {};
				void setBold(bool bold) {};

			private:
				bool m_Italic = false, m_Bold = false;
				char *m_Text;
			};
		}
	}
}