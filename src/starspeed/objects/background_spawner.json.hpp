#pragma once
#include "motor/object/gameobject.hpp"
#include <random>
#include "motor/components/sprite.hpp"
#include "starspeed/textures.hpp"
#include "star.hpp"
#include "starspeed/components/down_movement.hpp"
#include "motor/components/revolution.hpp"

namespace StarSpeed {

    //TODO REWRITE THIS


    class StableSucc : public Motor::GameObject {
    public:
        void onCreate() override {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> alph(0, 225);
            std::uniform_real_distribution<double> siz(32, 90);
            std::uniform_int_distribution<int> frametime(80, 160);
            transform()->color.set(255, 255, 255, (uint8) alph(mt));
            double size = siz(mt);
            transform()->scale.set(size);
            addComponent<Motor::SpriteAnimationComponent>(Tex::STABLE_SUCC);
            getComponent<Motor::SpriteAnimationComponent>()->setRowColumn(1, 45);
            getComponent<Motor::SpriteAnimationComponent>()->setFrameTime(frametime(mt));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(0, 0, 0, 50);
        }
        void render() override {
            Motor::GameObject::render();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (transform()->position.screen().getY() > 1080 * getriebe.getGame()->getRenderer()->heightDifference_) {
                destroy();
            }
            if (transform()->position.screen().getX() > 1920 * getriebe.getGame()->getRenderer()->widthDifference_) {
                destroy();
            }
        }
    };

    class UnStableSucc : public Motor::GameObject {
    public:
        void onCreate() override {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> alph(0, 225);
            std::uniform_real_distribution<double> siz(32, 90);
            std::uniform_int_distribution<int> frametime(80, 160);
            transform()->color.set(255, 255, 255, (uint8) alph(mt));
            double size = siz(mt);
            transform()->scale.set(size);
            addComponent<Motor::SpriteAnimationComponent>(Tex::UNSTABLE_SUCC);
            getComponent<Motor::SpriteAnimationComponent>()->setRowColumn(1, 45);
            getComponent<Motor::SpriteAnimationComponent>()->setFrameTime(frametime(mt));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(0, 0, 0, 50);
        }
        void render() override {
            Motor::GameObject::render();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (transform()->position.screen().getY() > 1080 * getriebe.getGame()->getRenderer()->heightDifference_) {
                destroy();
            }
            if (transform()->position.screen().getX() > 1920 * getriebe.getGame()->getRenderer()->widthDifference_) {
                destroy();
            }
        }
    };

    class Wheezerus : public Motor::GameObject {
    public:
        void onCreate() override {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> alph(0, 225);
            std::uniform_real_distribution<double> siz(32, 90);
            std::uniform_int_distribution<int> frametime(80, 160);
            transform()->color.set(255, 255, 255, (uint8) alph(mt));
            double size = siz(mt);
            transform()->scale.set(size);
            addComponent<Motor::SpriteAnimationComponent>(Tex::WHEEZERUS);
            getComponent<Motor::SpriteAnimationComponent>()->setRowColumn(1, 8);
            getComponent<Motor::SpriteAnimationComponent>()->setFrameTime(frametime(mt));
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(0, 0, 0, 50);
        }
        void render() override {
            Motor::GameObject::render();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (transform()->position.screen().getY() > 1080 * getriebe.getGame()->getRenderer()->heightDifference_) {
                destroy();
            }
            if (transform()->position.screen().getX() > 1920 * getriebe.getGame()->getRenderer()->widthDifference_) {
                destroy();
            }
        }
    };

    class Mathew : public Motor::GameObject {
    public:
        void onCreate() override {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> alph(0, 225);
            std::uniform_real_distribution<double> siz(32, 90);
            std::uniform_real_distribution<double> rev(0.02, 0.2);

            transform()->color.set(255, 255, 255, (uint8) alph(mt));
            double size = siz(mt);
            transform()->scale.set(size);
            addComponent<Motor::SpriteComponent>(Tex::MATHEW);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
            getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(0, 0, 0, 50);

            addComponent<Motor::RevolutionComponent>()->speed_ = rev(mt);

            getComponent<Motor::SpriteComponent>()->useSizeCenter();
        }
        void render() override {
            Motor::GameObject::render();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            if (transform()->position.screen().getY() > 1080 * getriebe.getGame()->getRenderer()->heightDifference_) {
                destroy();
            }
            if (transform()->position.screen().getX() > 1920 * getriebe.getGame()->getRenderer()->widthDifference_) {
                destroy();
            }
        }
    };


    class BackGroundSpawner : public Motor::GameObject {

        void spawnStar() {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist_x(-32, -16);
            std::uniform_real_distribution<double> dist_y(0, 1080);
            std::uniform_real_distribution<double> dist_speed(0.025, 0.1);
            Star *STAR = new Star();
            STAR->transform()->depth = -5;
            STAR->transform()->position.set(dist_x(mt), dist_y(mt));
            STAR->addComponent<SideMovement>()->speed_ = dist_speed(mt);
            STAR->addToCurrentScene(false);
        }

        float starCounter = 0;
        float planetCounter = 0;
        float sortCounter = 0;
        int* progress;
        void fixedUpdate() override {
            Motor::GameObject::fixedUpdate();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            starCounter += 0.1f * delta;
            sortCounter += 0.1f * delta;
            planetCounter += 0.1f * delta;

            if (8 < starCounter) {
                starCounter = 0;
                spawnStar();
            }

            if (500 < sortCounter) {
                getriebe.getGame()->getCurrentScene()->sortObjects();
                sortCounter = 0;
            }


            if (750 < planetCounter) {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_int_distribution<int> rnd(0, 4);
                std::uniform_real_distribution<double> dist_x(-32, -16);
                std::uniform_real_distribution<double> dist_y(0, 1080);
                std::uniform_real_distribution<double> dist_speed(0.025, 0.1);
                int d = rnd(mt);
                //UGLY BUT DONT CARE
                if(d == 0) {
                    UnStableSucc *STAR = new UnStableSucc();
                    STAR->transform()->depth = -5;
                    STAR->transform()->position.set(dist_x(mt), dist_y(mt));
                    STAR->addComponent<SideMovement>()->speed_ = dist_speed(mt);
                    STAR->addToCurrentScene();
                } else if(d == 1) {
                    StableSucc *STAR = new StableSucc();
                    STAR->transform()->depth = -5;
                    STAR->transform()->position.set(dist_x(mt), dist_y(mt));
                    STAR->addComponent<SideMovement>()->speed_ = dist_speed(mt);
                    STAR->addToCurrentScene();
                } else if(d == 2) {
                    Wheezerus* WHEEZE = new Wheezerus();
                    WHEEZE->transform()->depth = -5;
                    WHEEZE->transform()->position.set(dist_x(mt), dist_y(mt));
                    WHEEZE->addComponent<SideMovement>()->speed_ = dist_speed(mt);
                    WHEEZE->addToCurrentScene();
                } else {
                    Mathew* WHEEZE = new Mathew();
                    WHEEZE->transform()->depth = -5;
                    WHEEZE->transform()->position.set(dist_x(mt), dist_y(mt));
                    WHEEZE->addComponent<SideMovement>()->speed_ = dist_speed(mt);
                    WHEEZE->addToCurrentScene();
                }
                getriebe.getGame()->getCurrentScene()->sortObjects();
                planetCounter = 0;
            }
        }
    };
}