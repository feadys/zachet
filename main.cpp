#include <iostream>
#include "systeminfoserver.h"

int main()
{
    SystemInfoServer server;
    SystemInfo info = server.getSystemInfo();

    std::cout << "OS Name: " << info.osName << std::endl;
    std::cout << "OS Version: " << info.osVersion << std::endl;
    std::cout << "Service Pack: " << info.servicePack << std::endl;

    if (info.totalMemory.has_value())
        std::cout << "Total Memory: " << info.totalMemory.value() / (1024 * 1024) << " MB" << std::endl;
    else
        std::cout << "Total Memory: Unknown" << std::endl;

    if (info.availableMemory.has_value())
        std::cout << "Available Memory: " << info.availableMemory.value() / (1024 * 1024) << " MB" << std::endl;
    else
        std::cout << "Available Memory: Unknown" << std::endl;

    return 0;
}
