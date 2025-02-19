#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <array>
#include "scanner.hpp"

namespace network_scanner {

    std::vector<Device> ScanNetwork(const std::string& network) {
        std::vector<Device> devices;

        auto arp_devices = ArpScan(network);

        for (auto& device : arp_devices) {
            device.name = "scanner";
            devices.push_back(device);
        }

        return devices;
    }

    std::vector<Device> ArpScan(const std::string& network) {
        std::vector<Device> devices;

        std::string cmd = "sudo arp-scan " + network + " --interface=eth0 --localnet";

        std::array<char, 128> buffer;
        std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);

        if (!pipe) {
            std::cerr << "Ошибка при запуске arp-scan" << std::endl;
            return devices;
        }

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            std::string line(buffer.data());
            
            if (line.find("192.168.") != std::string::npos) {  
                devices.push_back(Device{line.substr(0, 15), "", true});
            }
        }
        
        return devices;
    }
}