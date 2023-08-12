#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "starspeed/resourcepack.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/textures.hpp"
#include "motor/components/text.hpp"
#include "starspeed/objects/swdavatar.hpp"
#include "fight.hpp"
#include "starspeed/discord.hpp"
#include "starspeed/splashs.hpp"
#include "starspeed/cursor.hpp"

namespace StarSpeed {

	class PlayButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/play.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 8, 1080 / 1.7);
			transform()->scale.set(128 * 1.5, 128 * 1.5);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->scale.set(128 * 1.5);
						if (triggerCursor) {
							CURSOR->resetTooltip();
							CURSOR->clickable(false);
							triggerCursor = false;
						}
					}
					else {
						transform()->scale.set(128 * 1.55);
						CURSOR->setTooltip("Play Game");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						CURSOR->resetTooltip();
						CURSOR->clickable(false);
						getriebe.getGame()->switchScene(new FightScene());
					}
				}
			}
		};
	};

	class OptionsButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/options.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 8 + ((128 * 1.5) * 2), 1080 / 1.7);
			transform()->scale.set(128 * 1.5, 128 * 1.5);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->scale.set(128 * 1.5);
						if (triggerCursor) {
							CURSOR->resetTooltip();
							CURSOR->clickable(false);
							triggerCursor = false;
						}
					}
					else {
						transform()->scale.set(128 * 1.55);
						CURSOR->setTooltip("Options");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						CURSOR->resetTooltip();
						CURSOR->clickable(false);
						getriebe.getGame()->switchScene(new FightScene());
					}
				}
			}
		};
	};

	class StarSpeedLogoTS : public Motor::GameObject {
	public:
		Motor::GameObject* SPLASH = nullptr;
		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 2, 1080 / 5.2);
			transform()->scale.set(76 * 9, 42 * 9);
		}
	};

	class DiscordJoinButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/discord.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 8 + 128 * 1.5, 1080 / 1.73);
			transform()->scale.set(128 * 1.5, 128 * 1.5);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->scale.set(128 * 1.5);
						if (triggerCursor) {
							CURSOR->resetTooltip();
							CURSOR->clickable(false);
							triggerCursor = false;
						}
					}
					else {
						transform()->scale.set(128 * 1.55);
						CURSOR->setTooltip("Join Discord Server");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						Fuchs::Utility::openURLInBrowser("https://discord.gg/47NsTqxEtK");
					}
				}
			}
		};
	};

	class TitleScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
			Motor::Scene::init(game);
			SDL_SetRenderDrawColor(getriebe.sdl_renderer(), 0, 0, 0, 255);

			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist_x(0, 1920);
			std::uniform_real_distribution<double> dist_y(0, 1080);
			std::uniform_real_distribution<double> dist_splash(0, SPLASHS.size());

			for (int i = 0; i < 150; i++) {
				Star* STAR = new Star();
				STAR->transform()->position.set(dist_x(mt), dist_y(mt));
				STAR->addToCurrentScene(false);
			}

			Motor::GameObject* CLOUD_BACKGROUND = new Motor::GameObject();
			CLOUD_BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/cloud.png"));
			CLOUD_BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			CLOUD_BACKGROUND->transform()->scale.set(6000, 10000);
			CLOUD_BACKGROUND->transform()->position.set(1920 / 2, -2750);
			CLOUD_BACKGROUND->transform()->color.setAlpha(12);
			CLOUD_BACKGROUND->addComponent<DownMovementComponent>()->speed_ = 0.04f;
			CLOUD_BACKGROUND->addToCurrentScene();


			PlayButton* playButton = new PlayButton();
			playButton->addToCurrentScene();

			DiscordJoinButton* discordButton = new DiscordJoinButton();
			discordButton->addToCurrentScene();

			OptionsButton* optionsButton = new OptionsButton();
			optionsButton->addToCurrentScene();

			Motor::GameObject* SWD_LOGO = new Motor::GameObject();
			SWD_LOGO->addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO);
			SWD_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			SWD_LOGO->transform()->position.set((449 / 3) / 1.8, 1080 - 82 / 3.5);
			SWD_LOGO->transform()->scale.set(449 / 3, 82 / 3);
			SWD_LOGO->addToCurrentScene();

			Motor::GameObject* STARSPEED_TEXT = new Motor::GameObject();
			STARSPEED_TEXT->addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->setContent("StarSpeed23 Version 0.0.5 ALPHA // F3 for DebugText");
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::RIGHT;
			STARSPEED_TEXT->transform()->position.set(1915, 1080 - 16);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->customScale_.set(18, 25);
			STARSPEED_TEXT->addToCurrentScene();

			Motor::GameObject* SPLASH_TEXT = new Motor::GameObject();
			std::string splashText = SPLASHS[dist_splash(mt)];
			if (splashText.contains("COLOR{")) {
				SPLASH_TEXT->addComponent<Motor::MultiColorText>(Tex::GAME_FONT);
				SPLASH_TEXT->getComponent<Motor::MultiColorText>()->setContent(splashText);
				SPLASH_TEXT->getComponent<Motor::MultiColorText>()->alignment_ = Motor::TextAlignment::MID;
			}
			else {
				SPLASH_TEXT->addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
				SPLASH_TEXT->getComponent<Motor::TextComponentBlended>()->setContent(splashText);
				SPLASH_TEXT->getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			}
			SPLASH_TEXT->transform()->position.set(1920 / 2, 1080 / 2.6);
			SPLASH_TEXT->transform()->scale.set(32, 32);
			SPLASH_TEXT->addToCurrentScene();

			Motor::GameObject* STARSPEED_LOGO_FLARE = new Motor::GameObject();
			STARSPEED_LOGO_FLARE->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_flare.png"));
			STARSPEED_LOGO_FLARE->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			STARSPEED_LOGO_FLARE->transform()->position.set(1920 * 0.53, 1080 / 15);
			STARSPEED_LOGO_FLARE->transform()->scale.set(320 * 7, 177 * 4);
			STARSPEED_LOGO_FLARE->transform()->color.set(255, 255, 255, 145);
			STARSPEED_LOGO_FLARE->addToCurrentScene();

			Motor::GameObject* STARSPEED_LOGO_FLARE_1 = new Motor::GameObject();
			STARSPEED_LOGO_FLARE_1->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_flare_1.png"));
			STARSPEED_LOGO_FLARE_1->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			STARSPEED_LOGO_FLARE_1->transform()->position.set(1920 * 0.53, 1080 / 15);
			STARSPEED_LOGO_FLARE_1->transform()->scale.set(480 * 2, 480 * 2);
			STARSPEED_LOGO_FLARE_1->transform()->color.set(255, 255, 255, 25);
			STARSPEED_LOGO_FLARE_1->addToCurrentScene();

			StarSpeedLogoTS* STARSPEED_LOGO = new StarSpeedLogoTS();
			STARSPEED_LOGO->SPLASH = SPLASH_TEXT;
			STARSPEED_LOGO->addToCurrentScene();


			Motor::GameObject* SUN_GLOW = new Motor::GameObject();
			SUN_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			SUN_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			SUN_GLOW->transform()->scale.set(5200, 5200);
			SUN_GLOW->transform()->position.set(1920 + 1200, 1080 + 1200);
			SUN_GLOW->transform()->color.set(214, 134, 54, 190);
			SUN_GLOW->addToCurrentScene();

			Motor::GameObject* SUN_GLOW_LEFT = new Motor::GameObject();
			SUN_GLOW_LEFT->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			SUN_GLOW_LEFT->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			SUN_GLOW_LEFT->transform()->scale.set(2000, 2000);
			SUN_GLOW_LEFT->transform()->position.set(0 - 750, 0 - 750);
			SUN_GLOW_LEFT->transform()->color.set(214, 134, 54, 190);
			SUN_GLOW_LEFT->addToCurrentScene();


			Motor::GameObject* MIDDLE_GLOW = new Motor::GameObject();
			MIDDLE_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			MIDDLE_GLOW->transform()->scale.set(5000, 5000);
			MIDDLE_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			MIDDLE_GLOW->transform()->color.set(29, 44, 79, 126);
			MIDDLE_GLOW->addToCurrentScene();

			Motor::GameObject* BACK_GLOW = new Motor::GameObject();
			BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK_GLOW->transform()->scale.set(5000, 4000);
			BACK_GLOW->transform()->position.set(-750, -750);
			BACK_GLOW->transform()->color.set(19, 37, 48, 175);
			BACK_GLOW->addToCurrentScene();

			Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
			BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK2_GLOW->transform()->scale.set(5000, 4000);
			BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			BACK2_GLOW->transform()->color.set(19, 37, 48, 95);
			BACK2_GLOW->addToCurrentScene();

			if (!discordApi.isCreated()) {
				SWDAvatar* SWD_AVATAR = new SWDAvatar();
				SWD_AVATAR->addToCurrentScene();
			}

			if (discordApi.isCreated()) {
				discordAvatar->addComponent<Motor::SpriteComponent>(avatarTexture);
				discordAvatar->addToCurrentScene();
			}
		}
	};
}