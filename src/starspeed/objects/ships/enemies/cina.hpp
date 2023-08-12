#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class CinaEnemy : public EnemyShip {
    public:
        CinaEnemy(): EnemyShip(Tex::CINA_ENEMY) {}
        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 0.35;
            shootCooldown = 45;
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