#pragma once

#ifdef WEB_BUILD
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <glew.h>
#endif

namespace Somnium {
	namespace Graphics {
		namespace Buffers {
			class Buffer {
				public:
					virtual ~Buffer() {};

					virtual inline void bind() const = 0;
					virtual inline void unbind() const = 0;

				protected:
					Buffer() {};

				};

		}
	}
}
