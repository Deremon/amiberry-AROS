cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_CROSSCOMPILING ON)
set(homedir $ENV{HOME})
set(CMAKE_C_COMPILER /usr/bin/x86_64-pc-aros-gcc)

set(CMAKE_CXX_COMPILER /usr/bin/x86_64-pc-aros-g++)

set(CMAKE_LINKER ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ld) 

set(CMAKE_C_COMPILER_AR ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ar --sysroot=${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development)

# from https://stackoverflow.com/questions/49763259/cmake-custom-toolchain-cmake-ar-and-cmake-cxx-archive-create
set(CMAKE_AR ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ar CACHE FILEPATH "" FORCE)

set(CMAKE_C_COMPILER_RANLIB ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ranlib --sysroot=${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development)

set(CMAKE_RANLIB ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ranlib)

# sysroot location
set(MYSYSROOT ${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development) 
set(CMAKE_FIND_ROOT_PATH "${MYSYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM     NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY     ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE     ONLY)

project (floppybridge VERSION 1.6.4)
enable_language(C CXX)
add_library(floppybridge STATIC # was SHARED
    src/ArduinoFloppyBridge.cpp
    src/ArduinoInterface.cpp
    src/CommonBridgeTemplate.cpp
    src/FloppyBridge.cpp
    src/ftdi.cpp
    src/GreaseWeazleBridge.cpp
    src/GreaseWeazleInterface.cpp
    src/pll.cpp
    src/RotationExtractor.cpp
    src/SerialIO.cpp
    src/SuperCardProBridge.cpp
    src/SuperCardProInterface.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)
#target_link_libraries(${PROJECT_NAME} PRIVATE pthread dl)
target_link_libraries(${PROJECT_NAME} PRIVATE lpthread)

#install(TARGETS ${PROJECT_NAME}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/amiberry
#  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
