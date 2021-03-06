#pragma once
#include <Windows.h>

void logger_set_tag(PCWSTR pszTag);

void logd(PCWSTR pszMsg);
void logdf(PCWSTR pszFmt, ...);
