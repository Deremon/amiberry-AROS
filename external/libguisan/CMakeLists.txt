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
project(guisan VERSION 1.1.0 DESCRIPTION "Guisan")
add_library(guisan STATIC
        src/actionevent.cpp
        src/cliprectangle.cpp
        src/color.cpp
        src/containerevent.cpp
        src/defaultfont.cpp
        src/event.cpp
        src/exception.cpp
        src/focushandler.cpp
        src/font.cpp
        src/genericinput.cpp
        src/graphics.cpp
        src/gui.cpp
        src/guisan.cpp
        src/image.cpp
        src/imagefont.cpp
        src/inputevent.cpp
        src/key.cpp
        src/keyevent.cpp
        src/keyinput.cpp
        src/mouseevent.cpp
        src/mouseinput.cpp
        src/rectangle.cpp
        src/selectionevent.cpp
        src/text.cpp
        src/widget.cpp
        src/sdl/sdl.cpp
        src/sdl/sdl2graphics.cpp
        src/sdl/sdlgraphics.cpp
        src/sdl/sdlimage.cpp
        src/sdl/sdlimageloader.cpp
        src/sdl/sdlinput.cpp
        src/sdl/sdltruetypefont.cpp
        src/widgets/button.cpp
        src/widgets/checkbox.cpp
        src/widgets/container.cpp
        src/widgets/dropdown.cpp
        src/widgets/icon.cpp
        src/widgets/imagebutton.cpp
        src/widgets/imagetextbutton.cpp
        src/widgets/inputbox.cpp
        src/widgets/label.cpp
        src/widgets/listbox.cpp
        src/widgets/messagebox.cpp
        src/widgets/progressbar.cpp
        src/widgets/radiobutton.cpp
        src/widgets/scrollarea.cpp
        src/widgets/slider.cpp
        src/widgets/tab.cpp
        src/widgets/tabbedarea.cpp
        src/widgets/textbox.cpp
        src/widgets/textfield.cpp
        src/widgets/togglebutton.cpp
        src/widgets/window.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf SDL2_image)
