#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class ZeninEnemy : public EnemyShip {
    public:
        ZeninEnemy(): EnemyShip(Tex::ZENIN_ENEMY) {}
        void shoot() override {

        }
    };
}