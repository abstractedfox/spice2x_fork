#include <winsock2.h>
#include <ws2tcpip.h>

#include "utils.h"

const char *inet_ntop(short af, const void *src, char *dst, DWORD size) {

    // prepare storage
    struct sockaddr_storage ss {};
    ZeroMemory(&ss, sizeof(ss));
    ss.ss_family = af;

    // IPv6 compatibility
    switch (af) {
        case AF_INET:
            ((struct sockaddr_in *) &ss)->sin_addr = *(struct in_addr *) src;
            break;
        case AF_INET6:
            ((struct sockaddr_in6 *) &ss)->sin6_addr = *(struct in6_addr *) src;
            break;
        default:
            return nullptr;
    }

    // convert to string
    int result = WSAAddressToStringA((struct sockaddr *) &ss, sizeof(ss), nullptr, dst, &size);

    // return on success
    return (result == 0) ? dst : nullptr;
}

BOOL CALLBACK _find_window_begins_with_cb(HWND wnd, LPARAM lParam) {
    auto windows = reinterpret_cast<std::vector<HWND> *>(lParam);
    windows->push_back(wnd);
    return TRUE;
}

std::wstring s2ws(const std::string &str) {
    if (str.empty()) {
        return std::wstring();
    }

    int length = MultiByteToWideChar(CP_ACP, 0, str.data(), -1, nullptr, 0);
    if (length == 0) {
        log_fatal("utils", "failed to get length of wide string: {}", get_last_error_string());
    }

    std::wstring buffer;
    buffer.resize(length - 1);

    length = MultiByteToWideChar(CP_ACP, 0, str.data(), -1, buffer.data(), length);
    if (length == 0) {
        log_fatal("utils", "failed to convert string to wide string: {}", get_last_error_string());
    }

    return buffer;
}

std::string ws2s(const std::wstring &wstr) {
    if (wstr.empty()) {
        return std::string();
    }

    int length = WideCharToMultiByte(CP_ACP, 0, wstr.data(), -1, nullptr, 0, nullptr, nullptr);
    if (length == 0) {
        log_fatal("utils", "failed to get length of wide string: {}", get_last_error_string());
    }

    std::string buffer;
    buffer.resize(length - 1);

    length = WideCharToMultiByte(CP_ACP, 0, wstr.data(), -1, buffer.data(), length, nullptr, nullptr);
    if (length == 0) {
        log_fatal("utils", "failed to convert string to wide string: {}", get_last_error_string());
    }

    return buffer;
}

bool acquire_shutdown_privs() {

    // check if already acquired
    static bool acquired = false;
    if (acquired)
        return true;

    // get process token
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return false;

    // get the LUID for the shutdown privilege
    TOKEN_PRIVILEGES tkp;
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // get the shutdown privilege for this process
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);

    // check for error
    bool success = GetLastError() == ERROR_SUCCESS;
    if (success)
        acquired = true;
    return success;
}
