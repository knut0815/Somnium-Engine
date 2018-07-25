#pragma once

#include "../../Maths/Vector2.h"
#include "../../Graphics/Shader.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace UI
		{
			class UIObject
			{
			public:
				UIObject() {};
				virtual ~UIObject() {};

				virtual void render() {};

				void setShader(Shader* shader) { m_Shader = shader; }

			protected:
				Maths::Vector2 m_Position;
				float m_Rotation;
				Shader *m_Shader;
				GLuint m_VAO, m_VBO;
			};
		}
	}
}