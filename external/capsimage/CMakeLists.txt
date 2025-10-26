cmake_minimum_required(VERSION 3.16)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_CROSSCOMPILING ON)
set(homedir $ENV{HOME})
set(CMAKE_C_COMPILER ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-gcc --sysroot=${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development)

set(CMAKE_CXX_COMPILER ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-g++ --sysroot=${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development)

set(CMAKE_LINKER ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ld) 

set(CMAKE_C_COMPILER_AR ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ar)

# from https://stackoverflow.com/questions/49763259/cmake-custom-toolchain-cmake-ar-and-cmake-cxx-archive-create
set(CMAKE_AR ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ar CACHE FILEPATH "" FORCE)

set(CMAKE_C_COMPILER_RANLIB ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ranlib)

set(CMAKE_RANLIB ${homedir}/arosbuilds/toolchain-core-x86_64/x86_64-aros-ranlib)

# sysroot location
set(MYSYSROOT ${homedir}/arosbuilds/core-linux-x86_64-d/bin/linux-x86_64/AROS/Development)
set(CMAKE_FIND_ROOT_PATH "${MYSYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM     NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY     ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE     ONLY)

project(capsimage)

set(PROJECT_TITLE CAPSImage)
set(PROJECT_TITLE_WIN32 CAPSImg)

set(MAJOR_VERSION 5)
set(MINOR_VERSION 1)

option(BUILD_SHARED_LIBS "Build a dynamic library instead of static library" OFF)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  option(BUILD_FRAMEWORK "Build a macOS framework instead of a shared library" OFF)
  set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
  set(BUILD_SHARED_LIBS ON)
endif()

option(ADD_INCLUDE_SUFFIX "Add major version suffix to include directory" OFF)
if (ADD_INCLUDE_SUFFIX)
  set(INCLUDE_SUFFIX ${MAJOR_VERSION})
  message(STATUS "Using '${INCLUDE_SUFFIX}' suffix on include directory")
endif()

include(CheckStructHasMember)
CHECK_STRUCT_HAS_MEMBER("struct dirent" d_type dirent.h HAVE_STRUCT_DIRENT_D_TYPE LANGUAGE CXX)

file(GLOB SOURCES src/Core/*.cpp src/CAPSImg/*.cpp src/Codec/*.cpp)
file(GLOB HEADERS src/Core/*.h src/CAPSImg/*.h src/Codec/*.h src/Device/*.h)
file(GLOB API_HEADERS src/LibIPF/*.h;src/Core/CommonTypes.h)
set(API_HEADERS ${API_HEADERS} ${CMAKE_BINARY_DIR}/CapsLibVersion.h)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${API_HEADERS})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#  VERSION ${MAJOR_VERSION}.${MINOR_VERSION}
#  SOVERSION ${MAJOR_VERSION}
#  CXX_STANDARD 11)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_BINARY_DIR}
  src/LibIPF
  src/CAPSImg
  src/Core
  src/Codec
  src/Device)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND BUILD_FRAMEWORK)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_TITLE}
    FRAMEWORK TRUE
    FRAMEWORK_VERSION C
    MACOSX_FRAMEWORK_IDENTIFIER com.kryoflux)
  set_source_files_properties(${API_HEADERS} PROPERTIES
    MACOSX_PACKAGE_LOCATION Headers/caps${INCLUDE_SUFFIX})
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")
endif()

if (WIN32)
  set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_TITLE_WIN32})
  target_include_directories(${PROJECT_NAME} PRIVATE src/Compatibility)
endif()

configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/config.h)
configure_file(src/LibIPF/CapsLibVersion.h.in ${CMAKE_BINARY_DIR}/CapsLibVersion.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H=1)

#install(TARGETS ${PROJECT_NAME}
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/amiberry
#  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#  FRAMEWORK DESTINATION "/Library/Frameworks"
#  PUBLIC_HEADER DESTINATION include/caps${INCLUDE_SUFFIX})

#if (NOT APPLE OR NOT BUILD_FRAMEWORK)
#  install(FILES ${API_HEADERS} DESTINATION include/caps${INCLUDE_SUFFIX})
#endif()
