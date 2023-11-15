#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {
    class CentEnemy : public EnemyShip {
    public:
        int expandCounter = 0;
        bool expanded = false;
        CentEnemy(): EnemyShip(Tex::Sheet::CENT_ROW, Tex::Sheet::CENT_COLUMN) {}

        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 0.02f;
            shootCooldown = 95;
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
                getComponent<Motor::SpriteSheetComponent>()->selectSprite(Tex::Sheet::CENT_EXPANDED_COLUMN, Tex::Sheet::CENT_EXPANDED_ROW);
                if(!getComponent<Motor::SpriteComponent>()->getTexture()->exists()) getComponent<Motor::SpriteComponent>()->getTexture()->load();
                expanded = true;     
            }
        }
    };
}