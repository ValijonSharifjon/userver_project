#pragma once

#include <string>
#include <vector>
namespace network_scanner {
    struct Device {
        std::string ip;
        std::string name;
        bool online;
    };

    std::vector<Device> ScanNetwork(const std::string& network);
    std::vector<Device> ArpScan(const std::string& network);
    std::string GetDeviceName(const std::string& ip);
    bool IsDeviceOnline(const std::string& ip);
}