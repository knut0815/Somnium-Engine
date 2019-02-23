#include "Colourise.h"

namespace Somnium
{
	namespace Graphics
	{
		namespace PostProcessing
		{
			namespace Filters
			{
				Colourise* Colourise::s_Instance = NULL;

				Colourise* Colourise::apply(float red, float green, float blue, float strength)
				{
					if (s_Instance == NULL)
						s_Instance = new Colourise();

					s_Instance->s_Shader->enable();
					s_Instance->s_Shader->setVector3("colourise", Maths::Vector3(red, green, blue));
					s_Instance->s_Shader->setFloat("strength", strength);

					return s_Instance;
				}
			}
		}
	}
}