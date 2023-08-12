#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class CentEnemy : public EnemyShip {
    public:
        int expandCounter = 0;
        bool expanded = false;
        CentEnemy(): EnemyShip(Tex::CENT_ENEMY) {}

        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 0.02f;
            shootCooldown = 85;
            health_ = 35;
            maxHealth_ = 35;
        }

        void shoot() override {
            if(expanded) {
                CentBullet* BULLET = new CentBullet();
                BULLET->transform()->position.set(transform()->position.getX(), transform()->position.getY() + 32);
                BULLET->addToCurrentScene(false);
            }
        }

        void fixedUpdate() override {
            EnemyShip::fixedUpdate();
            ++expandCounter;
            if(expandCounter == 175) {
                getComponent<Motor::SpriteComponent>()->setTexture(Tex::CENT_EXPANDED_ENEMY);
                if(!getComponent<Motor::SpriteComponent>()->getTexture()->exists()) getComponent<Motor::SpriteComponent>()->getTexture()->load();
                expanded = true;     
            }
        }
    };
}