#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class SawEnemy : public EnemyShip {
    public:
        SawEnemy(): EnemyShip(Tex::SAW_ENEMY) {}
        void shoot() override {

        }
    };
}