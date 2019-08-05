//
// Created by lior on 01/06/19.
//

#include <fstream> /* for open file and read his content */
#include "Device.hpp"

Device::Device(struct pcap_if device) {
    std::cout << "---------------------------------------------------" << std::endl;
    _name = std::string(device.name);
    std::cout << "Network device found: " << device.name << std::endl;
    if (device.description != nullptr)
        _description = std::string(device.description);

    if(!_description.empty())
        std::cout << "Description: " << _description << std::endl;

    _isLoopback =   (device.flags & PCAP_IF_LOOPBACK)   != 0;
    _isUp =         (device.flags & PCAP_IF_UP)         != 0;
    _isRunning =    (device.flags & PCAP_IF_RUNNING)    != 0;

    /* Get mac address */
    std::string deviceMacAddressFile;
    deviceMacAddressFile.append("/sys/class/net/");
    deviceMacAddressFile.append(device.name);
    deviceMacAddressFile.append("/address");
    _macAddress = getWholeFileContent(deviceMacAddressFile);
    _macAddress = _macAddress.substr(0,_macAddress.size()-1); /* remove last character (unwanted '\n') */

    /* Get IP Addresses */
    auto address = device.addresses;
    while(address != nullptr)
    {
        _deviceAddresses.emplace_back(*address);
        address = address->next;
    }
}

std::string Device::getWholeFileContent(const std::string &fileDirectory) {
    std::ifstream file(fileDirectory);
    if (!file.is_open())
    {
        std::cerr << "Can't open file " << fileDirectory << std::endl;
        return std::string();
    }
    return std::string ((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

const std::string &Device::getName() const {
    return _name;
}

const std::string &Device::getDescription() const {
    return _description;
}

const std::string &Device::getMacAddress() const {
    return _macAddress;
}

const std::vector<DeviceAddress> &Device::getDeviceAddresses() const {
    return _deviceAddresses;
}

bool Device::isLoopback() const {
    return _isLoopback;
}

bool Device::isUp() const {
    return _isUp;
}

bool Device::isRunning() const {
    return _isRunning;
}

bool Device::operator==(const Device &other) {
    return _name == other._name && _macAddress == other._macAddress && _description == other._description;
}

const std::string Device::toString() const {
    std::string str = "Device properties:\nName: " + _name + "\n";
    if (!_description.empty())
        str.append("Description: " + _description + "\n");
    if (!_macAddress.empty())
        str.append("Mac address: " + _macAddress + "\n");
    for (const auto& deviceAddress : _deviceAddresses)
    {
        if (!deviceAddress.isEmpty())
            str.append(deviceAddress.toString() + "\n");
    }
    if (_isLoopback)
        str.append("Link is Loopback\n");
    if (_isUp)
        str.append("Link is up\n");
    else
        str.append("Link is down\n");
    if (_isRunning)
        str.append("Link is running\n");
    else
        str.append("Link is not running\n");

    return str;
}

