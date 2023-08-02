#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class SawEnemy : public EnemyShip {
    public:
        SawEnemy(): EnemyShip(Tex::SAW_ENEMY) {}

        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 1.2f;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(255, 0, 0, 45);
        }

        void shoot() override {

        }
    };
}