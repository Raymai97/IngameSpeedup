#include "dll.h"
#include "logger.h"
#pragma comment(lib, "winmm.lib")

BOOL IS_WantFastFwd = TRUE;

DWORD WINAPI IS_timeGetTime(void)
{
	if (IS_WantFastFwd)
	{
		return ((DWORD)-1) - timeGetTime();
	}
	return timeGetTime();
}
