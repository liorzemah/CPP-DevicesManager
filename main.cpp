#include <vector>
#include <algorithm>
#include <iostream>
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h> /* for use DIR and openDir function */
#include <fstream>  /* for open file and read his content */
#include "Device/DeviceAddress.hpp"
#include "Device/DeviceList.hpp"
#include "Menu/Menu.hpp"

bool openDir(const std::string& folderDirectory)
{
    int len;
    struct dirent *pDirent;
    DIR *pDir;
    if (folderDirectory.empty())
    {
        std::cerr << "The directory is empty" << std::endl;
    }
    pDir = opendir (folderDirectory.c_str());
    if (pDir == NULL) {
        std::cerr << "Cannot open directory " << folderDirectory << std::endl;
        return false;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }
    closedir (pDir);
    return true;
}

std::string getWholeFileContent(const std::string& fileDirectory)
{
    std::ifstream file(fileDirectory);
    if (!file.is_open())
    {
        std::cerr << "Can't open file " << fileDirectory << std::endl;
        return std::string();
    }
    return std::string ((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
}

void func(const Device& dev)
{
    std::cout << "Call toString" << std::endl;
    std::cout << dev.toString() << std::endl;
}

void funcWith(const std::string& str)
{
    std::cout << "Call funcWith : " << str << std::endl;
}

void funcWithout()
{
    std::cout << "Call funcWithout : "  << std::endl;
}

bool exitMenu()
{
    std::cout << "Goodby..." << std::endl;
    exit(0);
}

/* All these function return True if they are success, else False */
bool printDevices();
bool selectDevices(const std::string& device);
bool printDeviceDetails(const std::string& device);
bool getDeviceByMac(const std::string& mac);
bool getDeviceByIp(const std::string& ip);
bool getUpDevices();
bool getRunningDevices();
bool loadList();

int menu()
{
    std::function<void()> f = std::bind(printDevices);
    f = std::bind(selectDevices, "fuck");
    Menu man(1);
    /* Make menu actions */
    man.addExitAction();
    man.addAction("Print list of devices", printDevices);
    man.addAction("Select device (select device and incoming into it's inner menu)", selectDevices, "Give name of device");
    man.addAction("Print device details", printDeviceDetails, "Give name of device");
    man.addAction("Get device by mac address", getDeviceByMac, "Give valid mac address");
    man.addAction("Get device by ip address", getDeviceByIp, "Give valid ipv4 or ipv6 address");
//    man.addAction("Get only devices there link is up", getUpDevices);
//    man.addAction("Get only devices there link is running", getRunningDevices);
    man.addAction("Load list", loadList);
//    man.addAction("Set flag", setListFlags); /* Do only set without updating the list, you can do it by use 'Load list' action */

    /* display menu */
    man.start();
}

int main() {
    DeviceList deviceList = DeviceList::instance();
    menu();
    return 0;
}


bool printDevices(){
    DeviceList deviceList = DeviceList::instance();
    std::cout << "List of devices:" << std::endl;
    for (int i=0;i<deviceList.getSize();i++)
    {
        std::cout << deviceList[i].getName() << std::endl;
    }
    return true;
}

bool selectDevices(const std::string& nameOfDevice){
    DeviceList deviceList = DeviceList::instance();
    Device device = deviceList.getDeviceByName(nameOfDevice);
    if (device.getName().empty())
        return false;
    /*  Create new sub-menu */
    std::cout << device.getName() << std::endl;
    return true;
}

bool printDeviceDetails(const std::string& nameOfDevice)
{
    DeviceList deviceList = DeviceList::instance();
    Device device = deviceList.getDeviceByName(nameOfDevice);
    if (device == Device::empty())
        return false;
    std::cout << device.toString() << std::endl;
    return true;
}

bool getDeviceByMac(const std::string& mac)
{
    Device device = DeviceList::instance().getDeviceByMac(mac);
    if (device == Device::empty())
        return false;
    std::cout << device.getName() << std::endl;
    return true;
}

bool getDeviceByIp(const std::string& ip){
    Device device = DeviceList::instance().getDeviceByIp(ip);
    if (device == Device::empty())
        return false;
    std::cout << device.getName() << std::endl;
    return true;
}

bool getUpDevices()
{
//    Device device = DeviceList::instance().getDeviceByMac(mac);
//    if (device == Device::empty())
//        return false;
//    std::cout << device.getName() << std::endl;
    return true;
}

bool getRunningDevices()
{
//    Device device = DeviceList::instance().getDeviceByMac(mac);
//    if (device == Device::empty())
//        return false;
//    std::cout << device.getName() << std::endl;
    return true;
}

bool loadList() {
    DeviceList::instance().updateList();
    return true;
}
