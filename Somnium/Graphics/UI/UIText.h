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

					glGenVertexArrays(1, &m_VAO);
					glGenBuffers(1, &m_VBO);
					glBindVertexArray(m_VAO);
					glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
					glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
					glEnableVertexAttribArray(0);
					glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					glBindVertexArray(0);
				}

				~UIText() {};

				void render();

				void setText(const std::string& text) {
					m_Text.assign(text); 
				};
				void setFont(Font *font) { m_Font = font; };
				void setSize(char *fontFilepath) {};
				
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