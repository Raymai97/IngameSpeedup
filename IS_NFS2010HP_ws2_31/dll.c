#include <WinSock2.h>
#include "dll.h"
#include "logger.h"
#pragma comment(lib, "ws2_32.lib")

BOOL IS_WantFastFwd = TRUE;

int WINAPI IS_WSARecv(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    (void)(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
    logdf(L"WSARecv");
    return 1;
}

static BOOL s_fWSARecvFrom;

int WINAPI IS_WSARecvFrom(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    struct sockaddr FAR* lpFrom,
    LPINT lpFromlen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    (void)(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine);
    logdf(L"WSARecvFrom");
    return 1;
}

DWORD WINAPI IS_WSAWaitForMultipleEvents(
    DWORD cEvents,
    const WSAEVENT FAR* lphEvents,
    BOOL fWaitAll,
    DWORD dwTimeout,
    BOOL fAlertable)
{
    (void)(cEvents, lphEvents, fWaitAll, dwTimeout, fAlertable);
    logdf(L"WSAWaitForMultipleEvents");
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_IDLE);
    Sleep(100);
    return 1;
}

int WINAPI IS_ws2recv(
    SOCKET s,
    char FAR* buf,
    int len,
    int flags)
{
    (void)(s, buf, len, flags);
    logdf(L"ws2recv");
    return 1;
}

int WINAPI IS_ws2recvfrom(
    SOCKET s,
    char FAR* buf,
    int len,
    int flags,
    struct sockaddr FAR* from,
    int FAR* fromlen)
{
    (void)(s, buf, len, flags, from, fromlen);
    logdf(L"ws2recvfrom");
    return 1;
}

int WINAPI IS_WSAGetLastError(void)
{
    return 0;
}
