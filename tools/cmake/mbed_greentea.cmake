# Copyright (c) 2020-2021 Arm Limited
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")

include(${CMAKE_CURRENT_LIST_DIR}/app.cmake)

# CMake Macro for generalizing CMake configuration across the greentea test suite with configurable parameters
# Macro args:
# TEST_NAME - Test suite name
# TEST_INCLUDE_DIRS - Test suite include directories for the test
# TEST_SOURCES - Test suite sources
# TEST_REQUIRED_LIBS - Test suite required libraries
# 
# calling the macro:
# mbed_greentea_add_test(
#    TEST_NAME mbed-platform-system-reset
#    TEST_INCLUDE_DIRS mbed_store
#    TEST_SOURCES foo.cpp bar.cpp
#    TEST_REQUIRED_LIBS mbed-kvstore mbed-xyz
# )

macro(mbed_greentea_add_test)
    set(options)
    set(singleValueArgs TEST_NAME)
    set(multipleValueArgs
        TEST_INCLUDE_DIRS
        TEST_SOURCES
        TEST_REQUIRED_LIBS
    )
    cmake_parse_arguments(MBED_GREENTEA
        "${options}"
        "${singleValueArgs}"
        "${multipleValueArgs}"
        ${ARGN}
    )

    set(TEST_NAME ${MBED_GREENTEA_TEST_NAME})

    add_subdirectory(${MBED_PATH} build)

    add_executable(${TEST_NAME})

    # Explicitly enable BUILD_TESTING until CTest is added to the Greentea client
    set(BUILD_TESTING ON)

    mbed_configure_app_target(${TEST_NAME})

    target_include_directories(${TEST_NAME}
        PRIVATE
            .
            ${MBED_GREENTEA_TEST_INCLUDE_DIRS}
    )

    target_sources(${TEST_NAME}
        PRIVATE
            main.cpp
            ${MBED_GREENTEA_TEST_SOURCES}
    )

    # The CMake MBED_TEST_LINK_LIBRARIES command-line argument is to get greentea test all dependent libraries.
    # For example:
    #  - To select mbed-os library, use cmake with -DMBED_TEST_LINK_LIBRARIES=mbed-os
    #  - To select baremetal library, use cmake with -DMBED_TEST_LINK_LIBRARIES=mbed-baremetal
    #  - To select baremetal with extra external error logging library to the test, use cmake with 
    #    -D "MBED_TEST_LINK_LIBRARIES=mbed-baremetal ext-errorlogging"
    if (DEFINED MBED_TEST_LINK_LIBRARIES)
        separate_arguments(MBED_TEST_LINK_LIBRARIES)
        list(APPEND MBED_GREENTEA_TEST_REQUIRED_LIBS ${MBED_TEST_LINK_LIBRARIES} mbed-greentea)
    else()        
        list(APPEND MBED_GREENTEA_TEST_REQUIRED_LIBS mbed-greentea)
    endif()

    target_link_libraries(${TEST_NAME}
        PRIVATE
            ${MBED_GREENTEA_TEST_REQUIRED_LIBS}
    )

    mbed_set_post_build(${TEST_NAME})

endmacro()
