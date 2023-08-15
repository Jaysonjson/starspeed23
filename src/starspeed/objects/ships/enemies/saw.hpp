#pragma once
#include "starspeed/objects/ships/enemy.hpp"

namespace StarSpeed {

    class SawIncoming : public Motor::GameObject {
        void onCreate() override {
            Motor::GameObject::onCreate();
            addComponent<Motor::SpriteComponent>(Tex::SQUARE_ALERT);
            getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->scale.set(73, 73);
            transform()->color.set(255, 255, 255, 101);
        }

        int alpha = 51;
        int cnt = 0;
        bool swi = true;
        void fixedUpdate() override {
            Motor::GameObject::fixedUpdate();
            if (swi) {
                alpha += 5;
            }
            else {
                alpha -= 5;
            }
            transform()->color.setAlpha(alpha);
            
            if (alpha > 255 || alpha < 50) {
                swi = !swi;
            }

            ++cnt;
            if (cnt > 75) {
                destroy();
            }
        }

    };

    class SawEnemy : public EnemyShip {
    public:
        SawEnemy(): EnemyShip(Tex::SAW_ENEMY) {}

        void onCreate() override {
            EnemyShip::onCreate();
            speed_ = 0.0f;
        }

        void shoot() override {

        }

        void fixedUpdate() {
            EnemyShip::fixedUpdate();
            speed_ += 0.02f;
        }
    };
}