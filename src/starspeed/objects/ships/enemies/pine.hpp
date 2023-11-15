#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class PineEnemy : public EnemyShip {
    public:
        PineEnemy(): EnemyShip(0,0) {}
        void shoot() override {

        }
    };
}