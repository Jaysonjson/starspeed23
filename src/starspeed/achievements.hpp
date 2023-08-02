#pragma once
#include "string"
#include "vector"
#include "motor/object/gameobject.hpp"
#include "textures.hpp"
#include "motor/components/sprite.hpp"
#include "resourcepack.hpp"
#include "motor/components/text.hpp"

namespace StarSpeed {
    class Achievement {
        std::string id_ = "";
        std::string description_ = "";
        bool unlocked_ = false;
    public:

        Achievement(std::string id, std::string desc): id_(id), description_(desc) {}

        std::string getID() {
            return id_;
        }

        std::string getDescription() {
            return description_;
        }

        bool isUnlocked() {
            return unlocked_;
        }

        void setUnlocked(bool unlocked) {
            this->unlocked_ = unlocked;
        }
    };

    extern std::vector<Achievement*> achievements;

    void unlockAchievement(std::string id);
    void unlockAchievement(Achievement* achievement);

    namespace Achmts {
        extern Achievement* START_GAME;
        extern Achievement* LOGIN_SWD;
        extern Achievement* DIE;
        extern Achievement* KILL_ENEMY;
        extern Achievement* WIN_ROUND;
    }

    void addAchievements();

    class AchievementUnlockHeader : public Motor::GameObject {
    public:
        int fadeCounter = 0;
        bool trigger = false;
        std::string description_ = "";
        void onCreate() {
            Motor::GameObject::onCreate();
            persistent_ = true;
            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/trophy.png"));
            getComponent<Motor::SpriteComponent>()->getTexture()->load();
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->scale.set(128, 128);
            transform()->position.set(1920 * 0.35, 1080 * 0.85);
            getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
            //hide();
            addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
            getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::LEFT;
            getComponent<Motor::TextComponentBlended>()->translate_.set(64, 8);

            addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
            getComponent<Motor::TextComponentBlended>(1)->setContent("ACHIEVEMENT UNLOCKED");
            getComponent<Motor::TextComponentBlended>(1)->alignment_ = Motor::TextAlignment::LEFT;
            getComponent<Motor::TextComponentBlended>(1)->translate_.set(64, -32);
            getComponent<Motor::TextComponentBlended>(1)->customScale_.set(std::string("ACHIEVEMENT UNLOCKED").size() * 2.5, 36 * 1.25);
        }

        void render() override {
            if (trigger) {
                Motor::GameObject::render();
            }
        }

        void fixedUpdate() override {
            Motor::GameObject::fixedUpdate();
            if (!isHidden()) {
                getComponent<Motor::TextComponentBlended>()->setContent(description_);
                getComponent<Motor::TextComponentBlended>()->customScale_.set(description_.size() * 1.5, 36 * 1.25);
                ++fadeCounter;
                if (fadeCounter > 125) {
                    fadeCounter = 0;
                    //hide();
                    trigger = false;
                }
            }
        }

    };

    extern AchievementUnlockHeader* ACHIEVEMENT_UNLOCK_HEADER;

}