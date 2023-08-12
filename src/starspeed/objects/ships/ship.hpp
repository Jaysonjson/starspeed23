#pragma once
#include "motor/object/gameobject.hpp"

namespace StarSpeed {
    class Ship : public Motor::GameObject {
    public:
        virtual void shoot() = 0;
    };
}