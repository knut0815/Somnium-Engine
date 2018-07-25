#include "UIText.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace UI
		{
			void UIText::render()
			{
				float x = m_Position.x, y = m_Position.y;
				m_Shader->enable();
				m_Shader->setVector3("textColor", m_Colour);
				glActiveTexture(GL_TEXTURE0);
				glBindVertexArray(m_VAO);

				// Iterate through all characters
				std::string::const_iterator c;
				
				for (c = m_Text.begin(); c != m_Text.end(); c++)
				{
					UICharacter ch = m_Font->getCharacterMap().at(*c);

					GLfloat xpos = x + ch.bearing.x * m_Scale;
					GLfloat ypos = y - (ch.size.y - ch.bearing.y) * m_Scale;

					GLfloat w = ch.size.x * m_Scale;
					GLfloat h = ch.size.y * m_Scale;
					// Update VBO for each character
					GLfloat vertices[6][4] = {
						{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
					};
					// Render glyph texture over quad
					glBindTexture(GL_TEXTURE_2D, ch.textureID);
					// Update content of VBO memory
					glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
					glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
					glBindBuffer(GL_ARRAY_BUFFER, 0);
					// Render quad
					glDrawArrays(GL_TRIANGLES, 0, 6);
					// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
					x += (ch.advance >> 6) * m_Scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
				}
				glBindVertexArray(0);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
}