#pragma once

#if !defined(_REENTRANT)
	#define _REENTRANT
#endif

#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>

	#define sleep(x)	Sleep(1000 * x);
#else
	#include <unistd.h>
#endif
