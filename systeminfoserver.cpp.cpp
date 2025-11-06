#include "systeminfoserver.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#endif

SystemInfo SystemInfoServer::getSystemInfo()
{
    SystemInfo info;
    info.osName = getOSName();
    info.osVersion = getOSVersion();
    info.servicePack = getServicePack();
    info.totalMemory = getTotalMemory();
    info.availableMemory = getAvailableMemory();
    return info;
}

std::string SystemInfoServer::getOSName()
{
#ifdef _WIN32
    return "Windows";
#elif __APPLE__
    return "macOS";
#elif __linux__
    return "Linux";
#else
    return "Unknown OS";
#endif
}

std::string SystemInfoServer::getOSVersion()
{
#ifdef _WIN32
    OSVERSIONINFOEXW info;
    ZeroMemory(&info, sizeof(info));
    info.dwOSVersionInfoSize = sizeof(info);
#pragma warning(push)
#pragma warning(disable:4996)
    if (!GetVersionExW(reinterpret_cast<OSVERSIONINFOW*>(&info)))
        return "Unknown Version";
#pragma warning(pop)
    return std::to_string(info.dwMajorVersion) + "." + std::to_string(info.dwMinorVersion);
#else
    struct utsname buffer;
    if (uname(&buffer) != 0)
        return "Unknown Version";
    return buffer.release;
#endif
}

std::string SystemInfoServer::getServicePack()
{
#ifdef _WIN32
    OSVERSIONINFOEXW info;
    ZeroMemory(&info, sizeof(info));
    info.dwOSVersionInfoSize = sizeof(info);
#pragma warning(push)
#pragma warning(disable:4996)
    if (!GetVersionExW(reinterpret_cast<OSVERSIONINFOW*>(&info)))
        return "None";
#pragma warning(pop)
    // Преобразуем wchar_t* в std::string
    std::wstring ws(info.szCSDVersion);
    return std::string(ws.begin(), ws.end());
#else
    return "None";
#endif
}

std::optional<uint64_t> SystemInfoServer::getTotalMemory()
{
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex))
        return statex.ullTotalPhys;
    return std::nullopt;
#else
    struct sysinfo info;
    if (sysinfo(&info) == 0)
        return static_cast<uint64_t>(info.totalram) * info.mem_unit;
    return std::nullopt;
#endif
}

std::optional<uint64_t> SystemInfoServer::getAvailableMemory()
{
#ifdef _WIN32
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    if (GlobalMemoryStatusEx(&statex))
        return statex.ullAvailPhys;
    return std::nullopt;
#else
    struct sysinfo info;
    if (sysinfo(&info) == 0)
        return static_cast<uint64_t>(info.freeram) * info.mem_unit;
    return std::nullopt;
#endif
}
