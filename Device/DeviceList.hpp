//
// Created by lior on 01/06/19.
//

#ifndef DEVICESMANAGER_DEVICELIST_HPP
#define DEVICESMANAGER_DEVICELIST_HPP

#include <vector>
#include <map>
#include "Device.hpp"

enum flag { FALSE = 0,
    TRUE  = 1,
    ANY   = 2};

class DeviceList {
private:
    std::string _lastUpdateTime;
    std::vector<Device> _devices;
    flag _loopbackFlag = ANY, _upFlag = ANY, _runningFlag = ANY;

    std::map<const std::string ,Device> _mapDevicesByName;
    std::map<const std::string ,Device> _mapDevicesByMac;
    std::map<const std::string ,Device> _mapDevicesByIp;

    explicit DeviceList(flag loopback = ANY, flag up = ANY, flag running = ANY); /* Create list of devices */

public:

    static DeviceList& instance(flag loopback = ANY, flag up = ANY, flag running = ANY)
    {
        static DeviceList _instance;
        _instance.setFlags(loopback,up,running);
        return _instance;
    }

    void updateList();
    void setFlags(flag loopback = ANY, flag up = ANY, flag running = ANY);
    Device &operator[] (int); /* Overloading [] operator to access elements in array style */
    auto const getSize() { return _devices.size(); };
    Device& getDeviceByName(const std::string& name);
    Device& getDeviceByMac(const std::string& name);
    Device& getDeviceByIp(const std::string& name);

};


#endif //DEVICESMANAGER_DEVICELIST_HPP
