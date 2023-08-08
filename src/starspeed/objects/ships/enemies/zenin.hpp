#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class ZeninEnemy : public EnemyShip {
    public:
        ZeninEnemy(): EnemyShip(Tex::ZENIN_ENEMY) {}

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