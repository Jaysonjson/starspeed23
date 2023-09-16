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

        float thrust_ = 0.9f;
        float decay_ = 0.97f;
        float maxSpeed_ = 4.5f;
        float turningSpeed_ = 3.25f;
        float speed_ = 0;
        float xSpeed_ = 0;
        float ySpeed_ = 0;

        int* progress_ = nullptr;
        float* fuel_ = nullptr;
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default.png"));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default_wing.png"));
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(234, 225, 125, 255);
            getComponent<Motor::SpriteComponent>(1)->center_.x = 45;
            getComponent<Motor::SpriteComponent>(1)->center_.y = 45;
            getComponent<Motor::SpriteComponent>(0)->center_.x = 45;
            getComponent<Motor::SpriteComponent>(0)->center_.y = 45;
            transform()->scale.set(90, 90);
            //transform()->position.set(1920 / 3, 0);
            getComponent<Motor::SpriteComponent>(0)->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>(1)->ignoreCamera_ = true;
            getriebe.getGame()->getCurrentScene()->getCamera().translate.set(-120, 450);

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(2)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(2)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(2)->customColor_.set(0, 0, 255, 45);
            getComponent<Motor::SpriteComponent>(2)->translate_.set(0, -10);
            getComponent<Motor::SpriteComponent>(2)->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>(2)->center_.y = 45;
            getComponent<Motor::SpriteComponent>(2)->center_.x = 45;

            addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
            getComponent<Motor::TextComponentBlended>()->setContent("Hold SPACE to shoot; Hold W to accelerate; A/D to strife Left/Right");
            getComponent<Motor::TextComponentBlended>()->ignoreCamera_ = true;
            getComponent<Motor::TextComponentBlended>()->translate_.set(0, 100);
            getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;


            transform()->position.set(1920 / 3, 1040);

        }

        void registerEvents() override {
            registerEvent(Motor::Events::keyUp.attach(&onKeyUp));
        }

        void shoot() override {
            PlayerBullet* BULLET = new PlayerBullet();
            BULLET->transform()->position.set(transform()->position.getX(), transform()->position.getY() - 32);
            BULLET->addToCurrentScene(false);
        }

        std::function<void(SDL_Event&)> onKeyUp = [this](SDL_Event& event) {
            /*if (event.key.keysym.sym == SDL_KeyCode::SDLK_SPACE) {
                shoot();
            }*/
        };


        int hueTimer = 0;
        int progressTimer = 0;
        bool accelerating = false;
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
            ++progressTimer;

            if (progressTimer == 35 && accelerating) {
                ++*progress_;
                progressTimer = 0;
            }

            if (progressTimer == 65) {
                ++*progress_;
                progressTimer = 0;
            }
            if (*progress_ == 100) {
                //getriebe.getGame()->switchScene(new TitleScreen());
                float delta = getriebe.getGame()->getDelta().deltaTime;
                getComponent<Motor::TransformComponent>()->position.add({ 0, -speed_ * 1.25f * delta });
                getriebe.getGame()->getCurrentScene()->getCamera().target = nullptr;
                getComponent<Motor::SpriteComponent>(0)->ignoreCamera_ = false;
                getComponent<Motor::SpriteComponent>(1)->ignoreCamera_ = false;
                progressTimer = 500;
            }
            if (transform()->position.screen().getY() < -64) {
                getriebe.getGame()->switchScene(new FightEnd());
            }
        }

        int shootCooldown = 100;
        void fixedUpdate() override {
            const uint8* key = SDL_GetKeyboardState(NULL);
            ++shootCooldown;
            if (key[SDL_Scancode::SDL_SCANCODE_SPACE] && 25 < shootCooldown) {
                shoot();
                shootCooldown = 0;
                getComponent<Motor::TextComponentBlended>()->setContent("");
            }
        }

        void render() override {
            GameObject::render();
            const uint8* key = SDL_GetKeyboardState(NULL);
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (key[SDL_Scancode::SDL_SCANCODE_D]) {
                if (transform()->position.getX() < 1390) {
                    /*transform()->position.add({speed_ * delta, 0});
                    getComponent<Motor::TextComponentBlended>()->setContent("");*/

                    transform()->rotation.increaseAngle(turningSpeed_);

                }
            }
            if (key[SDL_Scancode::SDL_SCANCODE_A]) {
                if (40 < transform()->position.getX()) {
                    /*transform()->position.add({-speed_ * delta, 0});
                    getComponent<Motor::TextComponentBlended>()->setContent("");*/
                    transform()->rotation.increaseAngle(-turningSpeed_);
                }
            }

            accelerating = false;
            if (key[SDL_Scancode::SDL_SCANCODE_LSHIFT] && *fuel_ > 0.1f) {
                thrust_ = 1.5f;
                maxSpeed_ = 15.5f;
                accelerating = true;
                *fuel_ -= 0.4f;
            }
            if (key[SDL_Scancode::SDL_SCANCODE_W]) {
                //getComponent<Motor::TransformComponent>()->position.add({ 0, -speed_ * 0.65f * delta });
                xSpeed_ += thrust_ * std::sin(transform()->rotation.getAngle() * (3.14 / 180));
                ySpeed_ += thrust_ * std::cos(transform()->rotation.getAngle() * (3.14 / 180));
                getComponent<Motor::TextComponentBlended>()->setContent("");
            }

            thrust_ = 0.9f;
            if (!accelerating) maxSpeed_ = 4.5f;

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