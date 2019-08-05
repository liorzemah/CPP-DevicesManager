cmake_minimum_required(VERSION 3.14)
project(DevicesManager)

set(CMAKE_CXX_STANDARD 17)

include(FindPCAP.cmake)
file(GLOB SOURCES Device/*.cpp Menu/*.cpp)
file(GLOB HEADERS Device/*.hpp Menu/*.hpp)

add_executable(DevicesManager ${SOURCES} ${HEADERS} main.cpp)
#add_library(DevicesManager ${SOURCES} ${HEADERS})

target_link_libraries(DevicesManager ${PCAP_LIBRARY})