#pragma once
#include "motor/object/gameobject.hpp"
#include <random>
#include "motor/components/sprite.hpp"
#include "motor/components/revolution.hpp"
#include "starspeed/textures.hpp"

namespace StarSpeed {
    class Explosion : public Motor::GameObject {
    public:
        void onCreate() override {
            Motor::GameObject::onCreate();

            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<float> rot(0, 360);
            std::uniform_real_distribution<float> sizernd(120, 200);

            float size = sizernd(mt);
            transform()->scale.set(size, size);
            addComponent<Motor::SpriteAnimationComponent>(Tex::EXPLOSION_SHEET);
            getComponent<Motor::SpriteAnimationComponent>()->setRowColumn(1, 4);
            getComponent<Motor::SpriteAnimationComponent>()->setFrameTime(35);
            getComponent<Motor::SpriteAnimationComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
            addComponent<Motor::RevolutionComponent>();
            getComponent<Motor::RevolutionComponent>()->speed_ = 4;

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(255, 0, 0, 60);
            getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(1)->customScale_.set(200, 200);

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(2)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(2)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(2)->customColor_.set(212, 110, 38, 40);
            getComponent<Motor::SpriteComponent>(2)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(2)->customScale_.set(500, 500);

            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(3)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(3)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(3)->customColor_.set(250, 178, 127, 10);
            getComponent<Motor::SpriteComponent>(3)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(3)->customScale_.set(1000, 1000);

            getComponent<Motor::SpriteComponent>(0)->useSizeCenter();
            getComponent<Motor::SpriteComponent>(1)->useSizeCenter();
            getComponent<Motor::SpriteComponent>(2)->useSizeCenter();
            getComponent<Motor::SpriteComponent>(3)->useSizeCenter();

            transform()->rotation.setAngle(rot(mt));
        }

        void onComponentEvent(Motor::IComponentEvent *eventData) override {
            if(eventData->id() == Motor::SpriteAnimationFinishEvent::id_) {
                auto* evt = dynamic_cast<Motor::SpriteAnimationFinishEvent *>(eventData);
                *evt->run_ = false;
                destroy();
            }
        }
    };
}