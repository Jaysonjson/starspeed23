#pragma once
#include "ship.hpp"
#include "motor/motor.hpp"
#include "motor/components/sprite.hpp"
#include "starspeed/objects/bullets/bullet.hpp"
#include <random>
namespace StarSpeed {

    class PlayerShip : public Ship {
    public:
        float speed_ = 1.05;
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default.png"));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ships/player/default/default_wing.png"));
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(234, 225, 125, 255);
            transform()->scale.set(64, 64);
            transform()->position.set(1920 / 3, 0);
            getComponent<Motor::SpriteComponent>(0)->ignoreCamera_ = true;
            getComponent<Motor::SpriteComponent>(1)->ignoreCamera_ = true;
            getriebe.getGame()->getCurrentScene()->getCamera().translate.set(-120, 450);

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(2)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(2)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(2)->customColor_.set(0, 0, 255, 45);
            getComponent<Motor::SpriteComponent>(2)->translatePosition_ = true;
            getComponent<Motor::SpriteComponent>(2)->translate_.set(0, -10);
            getComponent<Motor::SpriteComponent>(2)->translateExtraPostion_ = true;
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

        int shootCooldown = 100;
        void fixedUpdate() override {
            const uint8* key = SDL_GetKeyboardState(NULL);
            ++shootCooldown;
            if(key[SDL_Scancode::SDL_SCANCODE_SPACE] && 25 < shootCooldown) {
                shoot();
                shootCooldown = 0;
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

            /* NO WHEN MOVING UP, ENEMY SHIPS SHOULD BE FASTER DOWN INSTEAD! */
            if (key[SDL_Scancode::SDL_SCANCODE_W]) getComponent<Motor::TransformComponent>()->position.add({ 0, -speed_ * 0.45f * delta });
            //if (key[SDL_Scancode::SDL_SCANCODE_S]) getComponent<Motor::TransformComponent>()->position.add({ 0, speed_ * 0.75f * delta });
        }
    };
}