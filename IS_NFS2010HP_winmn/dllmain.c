#include "dll.h"
#include "logger.h"

static HINSTANCE DLL_hInst;
static DWORD IS_ThreadID;

BOOL IS_OnKeyUp(KBDLLHOOKSTRUCT* ph)
{
	if (ph->vkCode == VK_APPS)
	{
		IS_WantFastFwd = !IS_WantFastFwd;
		logdf(L"Toggled Want_Fast_Forward to %d", IS_WantFastFwd);
	}
	return FALSE;
}

LRESULT CALLBACK IS_HookProc_KBDLL(int nCode, WPARAM wParam, LPARAM lParam)
{
	BOOL fEatKeystroke = FALSE;
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_KEYUP:
		case WM_SYSKEYUP:
			fEatKeystroke = IS_OnKeyUp((KBDLLHOOKSTRUCT*)lParam);
			break;
		}
	}
	return fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam);
}

static DWORD CALLBACK IS_ThreadProc(LPVOID lpParam)
{
	MSG msg;
	(void)(lpParam);
	SetWindowsHookEx(WH_KEYBOARD_LL, IS_HookProc_KBDLL, DLL_hInst, 0);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return 0;
}

int APIENTRY DllMain(HINSTANCE hInstDLL, DWORD dwReason, LPVOID lpReserved)
{
	(void)(lpReserved);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		logger_set_tag(L"IS_NFS2010HP_winmn");
		logd(L"On DLL_PROCESS_ATTACH");
		DLL_hInst = hInstDLL;
		CreateThread(0, 0, IS_ThreadProc, 0, 0, &IS_ThreadID);
		logdf(L"IS_ThreadID = 0x%.8X", IS_ThreadID);
		break;
	case DLL_PROCESS_DETACH:
		logd(L"On DLL_PROCESS_DETACH");
		IS_ThreadID = 0;
		break;
	}
	return TRUE;
}
