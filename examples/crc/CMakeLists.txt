# Copyright (c) 2021 Arm Limited
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

add_library(sdfx-hal-example-crc OBJECT)

target_sources(sdfx-hal-example-crc
    PRIVATE
        main.c
)

target_link_libraries(sdfx-hal-example-crc
    PRIVATE
        mbed-os
)

add_compile_definitions(
    MBED_CONF_MBED_TRACE_ENABLE=1 
    MBED_TRACE_MAX_LEVEL=TRACE_LEVEL_DEBUG
)
