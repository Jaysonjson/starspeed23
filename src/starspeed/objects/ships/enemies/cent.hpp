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
            speed_ = 0.05f;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(255, 0, 0, 45);
             shootCooldown = 85;
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
            if(expandCounter == 120) {
                getComponent<Motor::SpriteComponent>()->setTexture(Tex::CENT_EXPANDED_ENEMY);
                if(!getComponent<Motor::SpriteComponent>()->getTexture()->exists()) getComponent<Motor::SpriteComponent>()->getTexture()->load();
                expanded = true;     
            }
        }
    };
}