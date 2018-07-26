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
				UIText(std::string text, Font* font, Maths::Vector2 position, Shader* shader)
					: m_Text(text), m_Font(font)
				{
					m_Position = position; 
					m_Shader = shader; 

					m_VAO.bind();
					m_VBO.bind();
					
					m_VAO.addBuffer(&m_VBO, 0);
					
					m_VBO.unbind();
					m_VAO.unbind();
				}

				~UIText() {};

				void render();

				void setText(const std::string& text) {
					m_Text.assign(text); 
				};
				void setFont(Font *font) { m_Font = font; };
				void setScale(float scale) { m_Scale = scale; }
				
				void setItalic(bool italic) {};
				void setBold(bool bold) {};

			private:
				bool m_Italic = false, m_Bold = false;
				float m_Scale = 1.f;
				Maths::Vector3 m_Colour = Maths::Vector3(1,1,1);
				Font const *m_Font;
				std::string m_Text;
			};
		}
	}
}