#include "logger.h"
#include <stdarg.h>

static PCWSTR logger_pszTag;

void logger_set_tag(PCWSTR pszTag)
{
	logger_pszTag = pszTag;
}

static void MyWriteLineStart(HANDLE hFile)
{
	SYSTEMTIME t;
	WCHAR szTimestamp[99];
	int cchTimestamp = 0;
	DWORD cbWri = 0;
	GetLocalTime(&t);
	cchTimestamp = wsprintfW(szTimestamp, L"[%.4u-%.2u-%.2u %.2u:%.2u:%.2u.%.3u]",
		t.wYear, t.wMonth, t.wDay,
		t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
	WriteFile(hFile, szTimestamp, cchTimestamp * sizeof(WCHAR), &cbWri, NULL);
	if (logger_pszTag)
	{
		WriteFile(hFile, L"[", sizeof(WCHAR), &cbWri, NULL);
		WriteFile(hFile, logger_pszTag, lstrlenW(logger_pszTag) * sizeof(WCHAR), &cbWri, NULL);
		WriteFile(hFile, L"]", sizeof(WCHAR), &cbWri, NULL);
	}
	WriteFile(hFile, L" ", sizeof(WCHAR), &cbWri, NULL);
}

void logd(PCWSTR pszMsg)
{
	WCHAR szPath[MAX_PATH] = { 0 };
	HANDLE hFile = 0;
	DWORD cbWri = 0;
	GetEnvironmentVariableW(L"IngameSpeedupLogPath", szPath, sizeof(szPath));
	hFile = CreateFileW(szPath, FILE_APPEND_DATA, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		hFile = 0;
		goto eof;
	}
	SetFilePointer(hFile, 0, NULL, FILE_END);
	if (GetFileSize(hFile, NULL) < 2)
	{
		WriteFile(hFile, "\xFF\xFE", 2, &cbWri, 0);
	}
	MyWriteLineStart(hFile);
	WriteFile(hFile, pszMsg, lstrlenW(pszMsg) * sizeof(WCHAR), &cbWri, NULL);
	WriteFile(hFile, L"\r\n", 4, &cbWri, NULL);
eof:
	if (hFile)
	{
		CloseHandle(hFile);
	}
}

void logdf(PCWSTR pszFmt, ...)
{
	WCHAR sz[1024];
	va_list ap;
	va_start(ap, pszFmt);
	wvsprintfW(sz, pszFmt, ap);
	logd(sz);
	va_end(ap);
}
