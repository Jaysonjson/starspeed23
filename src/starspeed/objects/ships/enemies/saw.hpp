#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class SawEnemy : public EnemyShip {
    public:
        SawEnemy(): EnemyShip(Tex::SAW_ENEMY) {}

        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 1.2f;
        }

        void shoot() override {

        }
    };
}