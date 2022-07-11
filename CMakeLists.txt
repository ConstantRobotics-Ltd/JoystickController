cmake_minimum_required(VERSION 3.13)



###############################################################################
## PROJECT
## name and version
###############################################################################
project(JoystickController LANGUAGES CXX)



###############################################################################
## CONFIGURATION
## project configuration
###############################################################################
SET(${PARENT}_JOYSTICK_CONTROLLER_EXAMPLE   ON  CACHE BOOL "" ${REWRITE_FORCE})



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################
# 3rdparty
add_subdirectory(3rdparty)

# src
add_subdirectory(src)

# test application
if (${PARENT}_JOYSTICK_CONTROLLER_EXAMPLE)
    add_subdirectory(example)
endif()
