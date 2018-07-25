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
				~UIObject() {};

				void setShader(Shader* shader) { m_Shader = shader; }

			private:
				Maths::Vector2 m_Position;
				float m_Rotation;
				Shader *m_Shader;
			};
		}
	}
}