#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class EsentEnemy : public EnemyShip {
    public:
        EsentEnemy(): EnemyShip(Tex::ESENT_ENEMY) {}
        void shoot() override {

        }
    };
}