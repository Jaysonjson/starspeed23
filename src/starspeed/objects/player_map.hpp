#pragma once
#include "ships/ship.hpp"
#include "motor/motor.hpp"
#include "motor/components/sprite.hpp"
#include "starspeed/objects/bullets/bullet.hpp"
#include "starspeed/scenes/titlescreen.hpp"
#include "starspeed/scenes/fight_end.hpp"
#include <random>
namespace StarSpeed {

    class PlayerMapShip : public Ship {
    public:
        //float speed_ = 1.05;

        float thrust_ = 0.1f;
        float decay_ = 0.97f;
        float maxSpeed_ = 0.95f;
        float turningSpeed_ = 3.55f;
        float speed_ = 0;
        float xSpeed_ = 0;
        float ySpeed_ = 0;

        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default.png"));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default_wing.png"));
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(234, 225, 125, 255);
            getComponent<Motor::SpriteComponent>(1)->center_.x = 16;
            getComponent<Motor::SpriteComponent>(1)->center_.y = 16;
            getComponent<Motor::SpriteComponent>(0)->center_.x = 16;
            getComponent<Motor::SpriteComponent>(0)->center_.y = 16;
            transform()->scale.set(41, 40);
            //transform()->position.set(1920 / 3, 0);
            getComponent<Motor::SpriteComponent>(0)->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>(1)->ignoreCamera_ = true;

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(2)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(2)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(2)->customColor_.set(0, 0, 255, 45);
            getComponent<Motor::SpriteComponent>(2)->translate_.set(0, -10);
            getComponent<Motor::SpriteComponent>(2)->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>(2)->center_.y = 20;
            getComponent<Motor::SpriteComponent>(2)->center_.x = 20;

            transform()->position.set(1920 / 2, 1080 / 2);
            transform()->depth = 50;
        }

        void shoot() override {}

        void registerEvents() override {}

        int hueTimer = 0;
        void update() override {
            GameObject::update();
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0, 255);
            ++hueTimer;
            if (hueTimer == 16) {
                getComponent<Motor::SpriteComponent>(1)->customColor_.set((int)dist(mt), (int)dist(mt), (int)dist(mt), 255);
                hueTimer = 0;
            }
        }

        void render() override {
            GameObject::render();
            const uint8* key = SDL_GetKeyboardState(NULL);
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (key[SDL_Scancode::SDL_SCANCODE_D]) {
                if (transform()->position.getX() < 1390) {
                    transform()->rotation.increaseAngle(turningSpeed_);

                }
            }
            if (key[SDL_Scancode::SDL_SCANCODE_A]) {
                if (40 < transform()->position.getX()) {
                    transform()->rotation.increaseAngle(-turningSpeed_);
                }
            }

            if (key[SDL_Scancode::SDL_SCANCODE_W]) {
                xSpeed_ += thrust_ * std::sin(transform()->rotation.getAngle() * (3.14 / 180));
                ySpeed_ += thrust_ * std::cos(transform()->rotation.getAngle() * (3.14 / 180));
            }

            xSpeed_ *= decay_;
            ySpeed_ *= decay_;

            speed_ = std::sqrt((xSpeed_ * xSpeed_) + (ySpeed_ * ySpeed_));
            if (speed_ > maxSpeed_) {
                xSpeed_ *= maxSpeed_ / speed_;
                ySpeed_ *= maxSpeed_ / speed_;
            }

            transform()->position.setX(transform()->position.getX() + xSpeed_);
            transform()->position.setY(transform()->position.getY() - ySpeed_);
            //if (key[SDL_Scancode::SDL_SCANCODE_S]) getComponent<Motor::TransformComponent>()->position.add({ 0, speed_ * 0.75f * delta });
        }
    };
}