#pragma once
#include "ship.hpp"
#include "motor/motor.hpp"
#include "motor/components/sprite.hpp"
#include <random>
#include "starspeed/resourcepack.hpp"
#include "starspeed/textures.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/objects/bullets/bullet.hpp"

namespace StarSpeed {

    class EnemyShip : public Ship {
    public:
        float speed_ = 0.25;
        float health_ = 10;
        float maxHealth_ = 10;
        Motor::Texture* TEX = nullptr;
        Motor::SpriteComponent* HEALTH_BAR = nullptr;
        EnemyShip(Motor::Texture* texture): TEX(texture) {}

        void onCreate() override {
            addComponent<Motor::SpriteComponent>(TEX);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteColliderComponent>();
            HEALTH_BAR = addComponent<Motor::SpriteComponent>(Tex::BAR_FULL);
            HEALTH_BAR->useCustomScale_ = true;
            HEALTH_BAR->customScale_.set(55, 0);
            HEALTH_BAR->useCustomColor_ = true;
            HEALTH_BAR->customColor_.set(255, 102, 102, 125);
            HEALTH_BAR->translate_.set(0, -48);
            transform()->scale.set(120, 120);
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(2)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(2)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(2)->customColor_.set(255, 0, 0, 45);
        }

        void update() override {
            Motor::GameObject::update();
            HEALTH_BAR->customScale_.set((health_ / maxHealth_) * 55, HEALTH_BAR->customScale_.y);
            std::vector<Motor::IColliderComponent*> colliders = getComponent<Motor::SpriteColliderComponent>()->collissionWithOther();
            if (!colliders.empty()) {
                for (Motor::IColliderComponent* collider : colliders) {
                    if(collider->getOwner()) {
                        PlayerBullet* PLAYER_BULLET = dynamic_cast<PlayerBullet*>(collider->getOwner());
                        if (PLAYER_BULLET && !PLAYER_BULLET->isHidden()) {
                            PLAYER_BULLET->hide();
                            health_ -= 10;
                            HEALTH_BAR->customColor_.setAlpha(125);
                            HEALTH_BAR->customScale_.set(HEALTH_BAR->customScale_.x, 7);
                        }

                        PlayerShip* PLAYER_SHIP = dynamic_cast<PlayerShip*>(collider->getOwner());
                        if(PLAYER_SHIP) {
                            health_ = 0;
                            PLAYER_SHIP->damage();
                        }
                    }
                }
            }
            if(health_ < 1) {
                destroy();
            }
        }
        
        void render() override {
            Motor::GameObject::render();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            transform()->position.add({0, speed_  * delta });
            if(transform()->position.screen().getY() > 1080) {
                destroy();
            }
        }

        int shootCooldownTimer = 0;
        int shootCooldown = 65;
        void fixedUpdate() override {
            Motor::GameObject::fixedUpdate();
            ++shootCooldownTimer;
            if(shootCooldown < shootCooldownTimer) {
                shoot();
                shootCooldownTimer = 0;
            }
        }

        void shoot() override {

        }
    };
}