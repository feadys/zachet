#pragma once
#include "systeminfo.h"

class SystemInfoServer
{
public:
    SystemInfo getSystemInfo();

private:
    std::string getOSName();
    std::string getOSVersion();
    std::string getServicePack();
    std::optional<uint64_t> getTotalMemory();
    std::optional<uint64_t> getAvailableMemory();
};
