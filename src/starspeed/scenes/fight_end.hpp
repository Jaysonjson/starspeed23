#pragma once
#include "motor/object/scene.hpp"
#include "random"
#include "starspeed/objects/star.hpp"
#include "starspeed/sceneswitcher.hpp"
namespace StarSpeed {

	class BackButton : public Motor::GameObject {
	public:
		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Back to Titlescreen");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;
			transform()->position.set(1920 / 2, 1080 / 1.1);
			transform()->scale.set(500, 64);
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						switchToTitleScreen();
					}
				}

				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						transform()->color.set(125, 125, 90, 255);
					}
					else {
						transform()->color.set(255, 255, 255, 255);
					}
				}
			}
		};
	};

    class FightEnd : public Motor::Scene {
    public:
        void init(Motor::Game* game) {

			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist_x(0, 1920);
			std::uniform_real_distribution<double> dist_y(0, 1080);

			for (int i = 0; i < 150; i++) {
				Star* STAR = new Star();
				STAR->transform()->position.set(dist_x(mt), dist_y(mt));
				STAR->addToCurrentScene(false);
			}

			BackButton* BACK_BUTTON = new BackButton();
			BACK_BUTTON->addToCurrentScene();

            Motor::GameObject* SUN_GLOW = new Motor::GameObject();
			SUN_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            SUN_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			SUN_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			SUN_GLOW->transform()->scale.set(5000, 5000);
			SUN_GLOW->transform()->position.set(1920 + 1200, 1080 + 1200);
			SUN_GLOW->transform()->color.set(214, 134, 54, 175);
			SUN_GLOW->addToCurrentScene();

			Motor::GameObject* MIDDLE_GLOW = new Motor::GameObject();
			MIDDLE_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			MIDDLE_GLOW->transform()->scale.set(5000, 5000);
			MIDDLE_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			MIDDLE_GLOW->transform()->color.set(29, 44, 79, 100);
			MIDDLE_GLOW->addToCurrentScene();

			Motor::GameObject* BACK_GLOW = new Motor::GameObject();
			BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK_GLOW->transform()->scale.set(5000, 4000);
			BACK_GLOW->transform()->position.set(-750, -750);
			BACK_GLOW->transform()->color.set(19, 37, 48, 175);
			BACK_GLOW->addToCurrentScene();

			Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
			BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK2_GLOW->transform()->scale.set(5000, 4000);
			BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			BACK2_GLOW->transform()->color.set(19, 37, 48, 50);
			BACK2_GLOW->addToCurrentScene();
        }
    };
}