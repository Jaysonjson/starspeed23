#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class FaireEnemy : public EnemyShip {
    public:
        FaireEnemy(): EnemyShip(Tex::FAIRE_ENEMY) {}
        void shoot() override {

        }
    };
}