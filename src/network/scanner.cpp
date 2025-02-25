#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <cctype>
#include "scanner.hpp"

namespace network_scanner {

    std::vector<Device> ScanNetwork(const std::string& network) {

        auto arp_devices = ArpScan(network);

        return arp_devices;
    }

    std::vector<Device> ArpScan(const std::string& network) {
        std::vector<Device> devices;

        std::string command = "arp-scan " + network + " 2>/dev/null";
        
        std::array<char, 256> buffer;
        std::string result;

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            std::cerr << "Ошибка при выполнении arp-scan!" << std::endl;
            return devices;
        }

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        pclose(pipe);

        std::istringstream iss(result);
        std::string line;
        while (std::getline(iss, line)) {
            if (line.empty() || !std::isdigit(line[0]))
                continue;

            std::istringstream linestream(line);
            std::string ip, mac;
            linestream >> ip >> mac; 

            if (!ip.empty()) {
                Device device;
                device.ip = ip;
                device.name = GetDeviceName(ip);       
                device.online = IsDeviceOnline(ip);  
                devices.push_back(device);
            }
        }

        return devices;
    }


    std::string GetDeviceName(const std::string& ip) {
        std::string command = "nslookup " + ip + " 2>/dev/null | grep name | awk '{print $4}'";
        std::array<char, 128> buffer;
        std::string result;

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) return "unknown";

        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
            result += buffer.data();
        }
        pclose(pipe);

        result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());

        return result.empty() ? "unknown" : result;
    }


    bool IsDeviceOnline(const std::string& ip) {
        std::string command = "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1";
        return system(command.c_str()) == 0;
    }
}