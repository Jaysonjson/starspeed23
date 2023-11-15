#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class EsentEnemy : public EnemyShip {
    public:
        EsentEnemy(): EnemyShip(0,0) {}
        void shoot() override {

        }
    };
}