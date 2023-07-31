#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class CentEnemy : public EnemyShip {
    public:
        CentEnemy(): EnemyShip(Tex::CENT_ENEMY) {}
        void shoot() override {

        }
    };
}