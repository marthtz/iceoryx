// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "iceoryx_binding_c/enums.h"
#include "iceoryx_binding_c/internal/cpp2c_enum_translation.hpp"
#include "iceoryx_posh/popo/user_trigger.hpp"

using namespace iox;
using namespace iox::popo;

extern "C" {
#include "iceoryx_binding_c/user_trigger.h"
}

iox_user_trigger_t iox_user_trigger_init(iox_user_trigger_storage_t* self)
{
    new (self) UserTrigger();
    return reinterpret_cast<iox_user_trigger_t>(self);
}

void iox_user_trigger_deinit(iox_user_trigger_t const self)
{
    self->~UserTrigger();
}

void iox_user_trigger_trigger(iox_user_trigger_t const self)
{
    self->trigger();
}

bool iox_user_trigger_has_triggered(iox_user_trigger_t const self)
{
    return self->hasTriggered();
}

void iox_user_trigger_reset_trigger(iox_user_trigger_t const self)
{
    self->resetTrigger();
}

iox_WaitSetResult iox_user_trigger_attach_to_ws(iox_user_trigger_t const self,
                                                iox_ws_t const wait_set,
                                                const uint64_t trigger_id,
                                                void (*trigger_callback)(iox_user_trigger_t))
{
    auto result = self->attachToWaitset(*wait_set, trigger_id, trigger_callback);
    if (!result.has_error())
    {
        return iox_WaitSetResult::WaitSetResult_SUCCESS;
    }

    return cpp2c::WaitSetResult(result.get_error());
}

void iox_user_trigger_detach_ws(iox_user_trigger_t const self)
{
    self->detachWaitset();
}

