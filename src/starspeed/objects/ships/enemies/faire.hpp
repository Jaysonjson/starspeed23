#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class FaireEnemy : public EnemyShip {
    public:
        FaireEnemy(): EnemyShip(0,0) {}
        void shoot() override {

        }
    };
}