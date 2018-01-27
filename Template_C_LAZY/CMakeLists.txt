cmake_minimum_required(VERSION 3.9)
project(simple)

set(CMAKE_C_STANDARD 99)

# make
add_custom_target(app
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# make SGX_DEBUG=0 (elease mode)
add_custom_target(app_realease
        COMMAND make SGX_DEBUG=0
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# make clean
add_custom_target(app_clean
        COMMAND make clean
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})