//
// Created by lior on 01/06/19.
//

#ifndef DEVICESMANAGER_DEVICEADDRESS_H
#define DEVICESMANAGER_DEVICEADDRESS_H

#include <string>
#include <pcap.h>

class DeviceAddress {
private:
    const std::string _ip;
    const std::string _subnetmask;
    const std::string _broadcast;
    const std::string _destination;
    bool _ipv4 = false;
    bool _ipv6 = false;
    std::string getSockAddr(struct sockaddr *sockAddr); /* Casting address from sockaddr structure to std::string */

public:
    explicit DeviceAddress(struct pcap_addr address);
    DeviceAddress(std::string ip, std::string subnetmask, std::string broadcast, std::string destination);
    bool ipIsEmpty() const { return _ip.empty(); }
    bool subnetmaskIsEmpty() const { return _subnetmask.empty(); }
    bool broadcastIsEmpty() const { return _broadcast.empty(); }
    bool destinationIsEmpty() const { return _destination.empty(); }
    bool isEmpty() const{ return _ip.empty() && _subnetmask.empty() && _broadcast.empty() && _destination.empty(); }
    bool isIPv4() const { return _ipv4; };
    bool isIPv6() const { return _ipv6; };
    const std::string &getIp() const;
    const std::string &getSubnetmask() const;
    const std::string &getBroadcast() const;
    const std::string &getDestination() const;
    const std::string toString() const;

};


#endif //DEVICESMANAGER_DEVICEADDRESS_H
