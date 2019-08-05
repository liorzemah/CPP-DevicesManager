#include <netinet/in.h>
#include <arpa/inet.h>
#include "DeviceAddress.hpp"

std::string DeviceAddress::getSockAddr(struct sockaddr *sockAddr) {
    std::string ip;
    char *ipPointer= nullptr;
    if (sockAddr == nullptr)
        return ip; /* empty message */

    switch (sockAddr->sa_family) {
        case AF_INET: {
            auto addr_in = reinterpret_cast<struct sockaddr_in *> (sockAddr);
            ipPointer = (char *) malloc(INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(addr_in->sin_addr), ipPointer, INET_ADDRSTRLEN);
            break;
        }
        case AF_INET6: {
            auto addr_in6 = reinterpret_cast<struct sockaddr_in6 *> (sockAddr);
            ipPointer = (char *) malloc(INET6_ADDRSTRLEN);
            inet_ntop(AF_INET6, &(addr_in6->sin6_addr), ipPointer, INET6_ADDRSTRLEN);
            break;
        }
        default:
            break;
    }
    if (ipPointer == nullptr)
        return ip; /* empty message */

    ip = std::string(ipPointer);
    free(ipPointer);
    return ip;
}

const std::string &DeviceAddress::getIp() const {
    return _ip;
}

const std::string &DeviceAddress::getSubnetmask() const {
    return _subnetmask;
}

const std::string &DeviceAddress::getBroadcast() const {
    return _broadcast;
}

const std::string &DeviceAddress::getDestination() const {
    return _destination;
}

const std::string DeviceAddress::toString() const {
    std::string str;
    if (isEmpty())
        return str;
    if (isIPv4())
        str = "Inet address: ";
    else
        str = "Inet6 address: ";

    if (!ipIsEmpty())
        str.append(_ip + " ");
    if (!broadcastIsEmpty())
        str.append("Broadcast: " + _broadcast + " ");
    if (!subnetmaskIsEmpty())
        str.append("Mask: " + _subnetmask + " ");
    if (!destinationIsEmpty())
        str.append("Destination: " + _destination + " ");
    return str;
}

DeviceAddress::DeviceAddress(struct pcap_addr address) : _ip(getSockAddr(address.addr)), _subnetmask(getSockAddr(address.netmask)),
                                                         _broadcast(getSockAddr(address.broadaddr)), _destination(getSockAddr(address.dstaddr)) {
    if (_ip.find('.') != std::string::npos)
        _ipv4 = true;
    else if (_ip.find(':') != std::string::npos)
        _ipv6 = true;
}

DeviceAddress::DeviceAddress(std::string ip, std::string subnetmask, std::string broadcast, std::string destination) : _ip(std::move(ip)), _subnetmask(std::move(subnetmask)), _broadcast(std::move(broadcast)), _destination(std::move(destination))
{
    if (_ip.find('.') >= 0)
        _ipv4 = true;
    else if (_ip.find(':') >= 0)
        _ipv6 = true;
}
