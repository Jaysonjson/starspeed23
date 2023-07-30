#pragma once
#include "ship.hpp"
#include "motor/motor.hpp"
#include "motor/components/sprite.hpp"
#include <random>
namespace StarSpeed {

    class PlayerShip : public Ship {
    public:
        float speed_ = 0.75;
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default.png"));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default_wing.png"));
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(234, 225, 125, 255);
            transform()->scale.set(64, 64);
            transform()->position.set(1920 / 3, 950);
        }

        void shoot() override {

        }
        int hueTimer = 0;
        void update() override {
            GameObject::update();
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0, 255);
            ++hueTimer;
            if(hueTimer == 16) {
                getComponent<Motor::SpriteComponent>(1)->customColor_.set((int)dist(mt), (int)dist(mt), (int)dist(mt), 255);
                hueTimer = 0;
            }
        }

        void render() override {
            GameObject::render();
            const uint8* key = SDL_GetKeyboardState(NULL);
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (key[SDL_Scancode::SDL_SCANCODE_D]) {
                if(transform()->position.getX() < 1390) {
                    transform()->position.add({ speed_ * delta, 0 });
                }
            }
            if (key[SDL_Scancode::SDL_SCANCODE_A]) {
                if(40 < transform()->position.getX()) {
                    transform()->position.add({ -speed_ * delta, 0 });
                }
            }
        }
    };
}