#pragma once
#include "motor/object/gameobject.hpp"
#include "motor/components/sprite.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/resourcepack.hpp"
#include "starspeed/textures.hpp"

namespace StarSpeed {
    class Bullet : public Motor::GameObject {
    public:
        float speed_ = 1.15;
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Tex::DEFAULT_BULLET);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
            addComponent<Motor::SpriteColliderComponent>();
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            transform()->scale.set(14, 14);
        }

        virtual void handleMovement() {
            float delta = getriebe.getGame()->getDelta().deltaTime;
            transform()->position.setY(transform()->position.getY() + speed_ * delta);
        }

        void update() {
            Motor::GameObject::update();
            handleMovement();
            if (transform()->position.screen().getY() > 1080) {
                destroy();
            }
            if (1 > transform()->position.screen().getY()) {
                destroy();
            }
        }

    };

    class EnemyBullet : public Bullet {
        void onCreate() override {
            Bullet::onCreate();
            transform()->color.set(115, 30, 30, 255);
        }
    };

    class CentBullet : public EnemyBullet {
        void fixedUpdate() override {
            EnemyBullet::fixedUpdate();
            transform()->scale.set(transform()->scale.x + 0.65f, transform()->scale.y + 1.25f);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(115, 30, 30, 175);
        }
    };

    class PlayerBullet : public Bullet {
    public:
        void onCreate() override {
            Bullet::onCreate();
            transform()->color.set(40, 122, 176, 255);
        }

        void handleMovement() override {
            float delta = getriebe.getGame()->getDelta().deltaTime;
            transform()->position.setY(transform()->position.getY() - speed_ * delta);
        }
        void update() override {
            Bullet::update();
        }
    };
}