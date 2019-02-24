#pragma once

#ifdef _WIN32
	#define SPRINTF sprintf_s
#else
	#define SPRINTF sprintf
#endif