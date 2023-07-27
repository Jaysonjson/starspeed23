#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "starspeed/resourcepack.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/textures.hpp"
#include "motor/components/text.hpp"


namespace StarSpeed {

	class PlayButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/play.png"));
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			getComponent<Motor::TransformComponent>()->position.set(1920 / 8, 1080 / 1.7);
			getComponent<Motor::TransformComponent>()->scale.set(128 * 1.5, 128 * 1.5);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->scale.set(128 * 1.5);
					}
					else {
						transform()->scale.set(128 * 1.55);
					}
				}
			}
		};
	};

	class TitleScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
			Motor::Scene::init(game);
			Motor::GameObject* STARSPEED_LOGO = new Motor::GameObject();
			STARSPEED_LOGO->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed.png"));
			STARSPEED_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			STARSPEED_LOGO->getComponent<Motor::TransformComponent>()->position.set(1920 / 2, 1080 / 5.2);
			STARSPEED_LOGO->getComponent<Motor::TransformComponent>()->scale.set(1160, 517);
			STARSPEED_LOGO->addToCurrentScene();

			PlayButton* playButton = new PlayButton();
			playButton->addToCurrentScene();

			Motor::GameObject* SWD_LOGO = new Motor::GameObject();
			SWD_LOGO->addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO);
			SWD_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			SWD_LOGO->getComponent<Motor::TransformComponent>()->position.set((449 / 3) / 1.8, 1080 - 82 / 3.5);
			SWD_LOGO->getComponent<Motor::TransformComponent>()->scale.set(449 / 3, 82 / 3);
			SWD_LOGO->addToCurrentScene();

			Motor::GameObject* STARSPEED_TEXT = new Motor::GameObject();
			STARSPEED_TEXT->addComponent<Motor::TextComponentBlended>(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->setContent("StarSpeed23 Version 0.1 ALPHA");
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::RIGHT;
			STARSPEED_TEXT->getComponent<Motor::TransformComponent>()->position.set(1915, 1080 - 16);
			STARSPEED_TEXT->getComponent<Motor::TransformComponent>()->scale.set(16, 16);
			STARSPEED_TEXT->addToCurrentScene();

			Motor::GameObject* SPLASH_TEXT = new Motor::GameObject();
			SPLASH_TEXT->addComponent<Motor::MultiColorText>(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
			SPLASH_TEXT->getComponent<Motor::MultiColorText>()->setContent("Here could be COLOR{\"color\":[144,0,0,255],\"text\":\" your \"}COLOR splash text!");
			SPLASH_TEXT->getComponent<Motor::MultiColorText>()->alignment_ = Motor::TextAlignment::MID;
			SPLASH_TEXT->getComponent<Motor::TransformComponent>()->position.set(1920 / 2, 1080 / 2.6);
			SPLASH_TEXT->getComponent<Motor::TransformComponent>()->scale.set(32, 32);
			SPLASH_TEXT->addToCurrentScene();
		}
	};
}