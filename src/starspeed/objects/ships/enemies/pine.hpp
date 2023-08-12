#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class PineEnemy : public EnemyShip {
    public:
        PineEnemy(): EnemyShip(Tex::PINE_ENEMY) {}
        void shoot() override {

        }
    };
}