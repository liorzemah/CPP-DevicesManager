#include <time.h>
#include "DeviceList.hpp"
#include "DeviceAddress.hpp"

DeviceList::DeviceList(flag loopback, flag up, flag running) : _loopbackFlag(loopback), _upFlag(up), _runningFlag(running){
    updateList();
}

void DeviceList::updateList() {
    char errorBuffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *devicesList;
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);
    _lastUpdateTime = std::string(asctime(timeinfo));
    std::cout << "Update time: " <<_lastUpdateTime << std::endl;

    if (pcap_findalldevs(&devicesList, errorBuffer) != 0) {
        std::cout << "Error finding _devices: " << std::string(errorBuffer) << std::endl;
        return;
    }
    while (devicesList != nullptr) {
        Device device(*devicesList);
        if ((_loopbackFlag == ANY ||
             (_loopbackFlag == FALSE && !device.isLoopback()) ||
             (_loopbackFlag == TRUE && device.isLoopback())) &&
            (_upFlag == ANY ||
             (_upFlag == FALSE && !device.isUp()) ||
             (_upFlag == TRUE && device.isUp())) &&
            (_runningFlag == ANY ||
             (_runningFlag == FALSE && !device.isRunning()) ||
             (_runningFlag == TRUE && device.isRunning()))) {
            _devices.push_back(device);
            _mapDevicesByName.insert(std::pair<const std::string, Device>(device.getName(), device));
            _mapDevicesByMac.insert(std::pair<const std::string, Device>(device.getMacAddress(), device));
            for (auto & deviceAddress : device.getDeviceAddresses())
                _mapDevicesByIp.insert(std::pair<const std::string, Device>(deviceAddress.getIp(), device));
        }
        devicesList = devicesList->next;
    }

    pcap_freealldevs(devicesList);
}

void DeviceList::setFlags(flag loopback, flag up, flag running) {
    _loopbackFlag = loopback;
    _upFlag = up;
    _runningFlag = running;
}

Device &DeviceList::operator[](int index) {
    if (!(index < _devices.size() && index >= 0))
    {
        std::cerr << "Device index out of bound, exiting" << std::endl;
        throw std::out_of_range("Device index out of bound, exiting");
    }
    return _devices[index];
}

Device& DeviceList::getDeviceByName(const std::string &name) {
    if (_mapDevicesByName.find(name) == _mapDevicesByName.end()) {
        std::cerr << "The given name is not of any device, Use action 1 to print all device names" << std::endl;
        return Device::empty();
    }
    return _mapDevicesByName.at(name);
}

Device& DeviceList::getDeviceByMac(const std::string &mac) {
    if (_mapDevicesByMac.find(mac) == _mapDevicesByMac.end()) {
        std::cerr << "The given mac address is not of any device" << std::endl;
        return Device::empty();
    }
    return _mapDevicesByMac.at(mac);
}

Device& DeviceList::getDeviceByIp(const std::string &ip) {
    if (_mapDevicesByIp.find(ip) == _mapDevicesByIp.end()) {
        std::cerr << "The given ip address is not of any device" << std::endl;
        return Device::empty();
    }
    return _mapDevicesByIp.at(ip);
}






