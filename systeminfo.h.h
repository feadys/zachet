#pragma once
#include <string>
#include <optional>
#include <cstdint>

struct SystemInfo {
    std::string osName;
    std::string osVersion;
    std::string servicePack;
    std::optional<uint64_t> totalMemory;     // В байтах
    std::optional<uint64_t> availableMemory; // В байтах
};
