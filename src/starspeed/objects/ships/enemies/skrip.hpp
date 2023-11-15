#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class SkripEnemy : public EnemyShip {
    public:
        SkripEnemy(): EnemyShip(0, 0) {}
        void shoot() override {

        }
    };
}