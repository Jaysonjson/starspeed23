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
        float speed_ = 0.45;
        Motor::Texture* TEX = nullptr;

        EnemyShip(Motor::Texture* texture): TEX(texture) {}

        void onCreate() override {
            addComponent<Motor::SpriteComponent>(TEX);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteColliderComponent>();
            transform()->scale.set(93, 93);
        }

        void update() override {
            Motor::GameObject::update();
            std::vector<Motor::IColliderComponent*> colliders = getComponent<Motor::SpriteColliderComponent>()->collissionWithOther();
            if (colliders.size() > 0) {
                for (Motor::IColliderComponent* collider : colliders) {
                    if(collider->getOwner()) {
                        PlayerBullet* PLAYER_BULLET = dynamic_cast<PlayerBullet*>(collider->getOwner());
                        if (PLAYER_BULLET && !PLAYER_BULLET->isHidden()) {
                            //PLAYER_BULLET->onHit(this);
                            //PLAYER_BULLET->removeComponent<Motor::SpriteColliderComponent>();
                            PLAYER_BULLET->hide();
                            destroy();
                            //PLAYER_BULLET->onHit(this);
                        }
                    }
                }
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
        int shootCooldown = 45;
        void fixedUpdate() override {
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