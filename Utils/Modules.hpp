#pragma once
#include "../Utils/InputTypes.hpp"
#include <set>

namespace Modules {
    namespace Aimbot {
        InputKeyType AimBind = InputKeyType::MOUSE_Right;
    }

    namespace Triggerbot {
        bool Enabled = true;
        bool OnADS = true;
        bool HipfireShotguns = false;
        float Range = 200;
    };
}