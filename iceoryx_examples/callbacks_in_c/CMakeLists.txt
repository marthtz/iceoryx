# Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
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
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.5)
project(example_callbacks_in_c)

include(GNUInstallDirs)

find_package(iceoryx_posh CONFIG REQUIRED)
find_package(iceoryx_binding_c CONFIG REQUIRED)
find_package(iceoryx_utils CONFIG REQUIRED)

get_target_property(ICEORYX_CXX_STANDARD iceoryx_posh::iceoryx_posh CXX_STANDARD)
include(IceoryxPlatform)

add_executable(iox-ex-c-callbacks-publisher ./ice_c_callbacks_publisher.c)
set_source_files_properties(./ice_c_callbacks_publisher.c PROPERTIES LANGUAGE C)
target_link_libraries(iox-ex-c-callbacks-publisher
    iceoryx_binding_c::iceoryx_binding_c
)
target_compile_options(iox-ex-c-callbacks-publisher PRIVATE ${ICEORYX_WARNINGS} ${ICEORYX_SANITIZER_FLAGS})

add_executable(iox-ex-c-callbacks-subscriber ./ice_c_callbacks_subscriber.c)
set_source_files_properties(./ice_c_callbacks_subscriber.c PROPERTIES LANGUAGE C)
target_link_libraries(iox-ex-c-callbacks-subscriber
    iceoryx_binding_c::iceoryx_binding_c
)
target_compile_options(iox-ex-c-callbacks-subscriber PRIVATE ${ICEORYX_WARNINGS} ${ICEORYX_SANITIZER_FLAGS})

set_target_properties(
    iox-ex-c-callbacks-subscriber
    iox-ex-c-callbacks-publisher
  PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD ${ICEORYX_CXX_STANDARD}
    POSITION_INDEPENDENT_CODE ON
)

install(
    TARGETS iox-ex-c-callbacks-publisher iox-ex-c-callbacks-subscriber 
    RUNTIME DESTINATION bin
)
