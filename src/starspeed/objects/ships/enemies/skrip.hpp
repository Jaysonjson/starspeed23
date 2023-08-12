#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class SkripEnemy : public EnemyShip {
    public:
        SkripEnemy(): EnemyShip(Tex::SKRIP_ENEMY) {}
        void shoot() override {

        }
    };
}