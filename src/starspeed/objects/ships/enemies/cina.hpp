#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class CinaEnemy : public EnemyShip {
    public:
        CinaEnemy(): EnemyShip(Tex::CINA_ENEMY) {}
        void shoot() override {

        }
    };
}