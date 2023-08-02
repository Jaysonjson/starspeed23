#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class ZeninEnemy : public EnemyShip {
    public:
        ZeninEnemy(): EnemyShip(Tex::ZENIN_ENEMY) {}

        void onCreate() override {
            EnemyShip::onCreate();
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(255, 0, 0, 45);
        }

        void shoot() override {
            EnemyBullet* BULLET = new EnemyBullet();
            BULLET->transform()->position.set(transform()->position.getX() - 16, transform()->position.getY() + 32);
            BULLET->addToCurrentScene(false);
            EnemyBullet* BULLET2 = new EnemyBullet();
            BULLET2->transform()->position.set(transform()->position.getX() + 16, transform()->position.getY() + 32);
            BULLET2->addToCurrentScene(false);
        }
    };
}