//
// Created by lior on 01/06/19.
//

#ifndef DEVICESMANAGER_DEVICE_HPP
#define DEVICESMANAGER_DEVICE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "DeviceAddress.hpp"

class Device {

private:
    std::string _name;                             /* name of device */
    std::string _description;                      /* textual description of interface, or empty string */
    std::string _macAddress;                       /* device mac address */
    std::vector<DeviceAddress> _deviceAddresses;   /* List of device addresses */
    bool _isLoopback = false;
    bool _isUp = false;
    bool _isRunning = false;
public:
    explicit Device(struct pcap_if pcapDevice);
    Device()= default;
    static Device& empty()
    {
        static Device instance;
        return instance;
    }

    const std::string &getName() const;

    const std::string &getDescription() const;

    const std::string &getMacAddress() const;

    const std::vector<DeviceAddress> &getDeviceAddresses() const;

    bool isLoopback() const;

    bool isUp() const;

    bool isRunning() const;

    bool operator==(const Device& other);

    const std::string toString() const;
private:

    std::string getWholeFileContent(const std::string& fileDirectory);
};


#endif //DEVICESMANAGER_DEVICE_HPP
