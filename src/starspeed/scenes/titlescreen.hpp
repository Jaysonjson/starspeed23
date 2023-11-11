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
#include "starspeed/utility.hpp"
#include "starspeed/scenes/cell_map.hpp"
#include "motor/sound/sound.hpp"
#include "motor/content/music.hpp"
#include "starspeed/objects/music_handler.hpp"
#include "motor/gameobjects/debugtext.hpp"
#include "dm_titlescreen.hpp"

namespace StarSpeed {

	constexpr int buttonStart = 1920 / 4.9;

	class PlayButton : public Motor::GameObject {
	public:
		//Motor::DynamicTexture* SELECTED = new Motor::DynamicTexture(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/play_selected.png"));
		Motor::DynamicTexture* DEFAULT = new Motor::DynamicTexture(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/play.png"));
		void onCreate() {
			//SELECTED->load();
			DEFAULT->load();
			addComponent<Motor::DynamicSpriteComponent>(DEFAULT);
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(buttonStart, 1080 / 1.7);
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
							//getComponent<Motor::DynamicSpriteComponent>()->setTexture(DEFAULT);
						}
					}
					else {
						transform()->scale.set(128 * 1.55);
						CURSOR->setTooltip("Play Game");
						CURSOR->clickable(true);
						triggerCursor = true;
						//getComponent<Motor::DynamicSpriteComponent>()->setTexture(DEFAULT);
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						CURSOR->resetTooltip();
						CURSOR->clickable(false);
						getriebe.getGame()->switchScene(new CellmapScene());
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
			transform()->position.set(buttonStart + ((128 * 1.75) * 2), 1080 / 1.7);
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

	class SaveFolder : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/save_game.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(buttonStart + ((128 * 1.75) * 3), 1080 / 1.7);
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
						CURSOR->setTooltip("Open Save Game Folder");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						Fuchs::Utility::openDirectoryInFileManager(Motor::Path::docs);
					}
				}
			}
		};
	};

	class CreditsButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/credits.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(buttonStart + ((128 * 1.75) * 4), 1080 / 1.7);
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
						CURSOR->setTooltip("StarSpeed23 Credits");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
					}
				}
			}
		};
	};

	class ExitButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/exit.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(buttonStart + ((128 * 1.75) * 5), 1080 / 1.7);
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
						CURSOR->setTooltip("Exit to Desktop");
						CURSOR->clickable(true);
						triggerCursor = true;
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						getriebe.getGame()->running_ = false;
					}
				}
			}
		};
	};

	class StarSpeedLogoTS : public Motor::GameObject {
	public:
		Motor::GameObject* SPLASH = nullptr;
		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_xr.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 2, 1080 / 4.65);
			transform()->scale.set(76 * 9, 42 * 9);
		}
	};

	class DiscordJoinButton : public Motor::GameObject {
	public:

		void onCreate() {
			addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/buttons/discord.png"));
			getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(buttonStart + 128 * 1.75, 1080 / 1.7);
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

    class SWDLogoTS : public Motor::GameObject {
    public:

        void onCreate() {
            addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO_WIDE);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->position.set((235) / 1.8, 1080 - 45);
            transform()->scale.set(235, 45);
            addComponent<Motor::SpriteColliderComponent>();
            getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
            getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
        }

        bool triggerCursor = false;
        void onComponentEvent(Motor::IComponentEvent* eventData) override {
            if (eventData->id() == "collider") {
                Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
                if (colliderEvent->type == Motor::HOVER) {
                    if (!colliderEvent->onObject) {
                        if (triggerCursor) {
                            CURSOR->clickable(false);
                            triggerCursor = false;
                        }
                    }
                    else {
                        CURSOR->clickable(true);
                        triggerCursor = true;
                    }
                }
                if (colliderEvent->type == Motor::CLICK_UP) {
                    if (colliderEvent->onObject) {
                        getriebe.getGame()->switchScene(new DMTitleScreen());
                    }
                }
            }
        };
    };

    class TestSheet : public Motor::GameObject {
    public:

        void onCreate() override {
            Motor::GameObject::onCreate();
            addComponent<Motor::SpriteAnimationComponent>(Motor::ResourceLocation(resourcePackMod, "/sprites/explosion_sheet.png"));
            getComponent<Motor::SpriteAnimationComponent>()->setRowColumn(1, 4);
            getComponent<Motor::SpriteAnimationComponent>()->setFrameTime(80);
            transform()->scale.set(128, 128);
            transform()->position.set(500, 500);
        }

        void onComponentEvent(Motor::IComponentEvent *eventData) override {
            if(eventData->id() == Motor::SpriteAnimationFinishEvent::id_) {
                MOTOR_LOG("Finished");
                Motor::SpriteAnimationFinishEvent* evt = dynamic_cast<Motor::SpriteAnimationFinishEvent *>(eventData);
                //*evt->run_ = false;
            }
        }

    };

	class TitleScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
			Motor::Scene::init(game);
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist_x(0, 1920);
			std::uniform_real_distribution<double> dist_y(0, 1080);
			std::uniform_real_distribution<double> dist_splash(0, SPLASHES.size());

			for (int i = 0; i < 150; i++) {
				Star* STAR = new Star();
				STAR->transform()->position.set(dist_x(mt), dist_y(mt));
				STAR->addToCurrentScene(false);
			}

			Motor::GameObject* CLOUD_BACKGROUND = new Motor::GameObject();
			Motor::DynamicTexture* CLOUD_BACKGROUND_TEX = new Motor::DynamicTexture(Motor::ResourceLocation(resourcePackMod, "sprites/cloud.png"));
			CLOUD_BACKGROUND_TEX->interpolated_ = true;
			CLOUD_BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(CLOUD_BACKGROUND_TEX);
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

			SaveFolder* saveFolder = new SaveFolder();
			saveFolder->addToCurrentScene();

			CreditsButton* creditsButton = new CreditsButton();
			creditsButton->addToCurrentScene();

			ExitButton* exitButton = new ExitButton();
			exitButton->addToCurrentScene();

            SWDLogoTS* SWD_LOGO = new SWDLogoTS();
			SWD_LOGO->addToCurrentScene();

			Motor::GameObject* STARSPEED_TEXT = new Motor::GameObject();
			STARSPEED_TEXT->addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->setContent("StarSpeed23 Version 0.0.6 ALPHA // F3 for DebugText");
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::RIGHT;
			STARSPEED_TEXT->transform()->position.set(1915, 1080 - 16);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->customScale_.set(18, 25);
			STARSPEED_TEXT->getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;
			STARSPEED_TEXT->addToCurrentScene();

			Motor::GameObject* SPLASH_TEXT = new Motor::GameObject();
			std::string splashText = SPLASHES[dist_splash(mt)];
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
			SPLASH_TEXT->transform()->position.set(1920 / 2, 1080 / 2.3);
			SPLASH_TEXT->transform()->scale.set(38, 38);
			SPLASH_TEXT->addToCurrentScene();

			Motor::GameObject* STARSPEED_LOGO_FLARE = new Motor::GameObject();
			STARSPEED_LOGO_FLARE->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_flare.png"));
			STARSPEED_LOGO_FLARE->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			STARSPEED_LOGO_FLARE->transform()->position.set(1920 * 0.53, 1080 / 11);
			STARSPEED_LOGO_FLARE->transform()->scale.set(320 * 7, 177 * 4);
			STARSPEED_LOGO_FLARE->transform()->color.set(255, 255, 255, 145);
			STARSPEED_LOGO_FLARE->addToCurrentScene();

			Motor::GameObject* STARSPEED_LOGO_FLARE_1 = new Motor::GameObject();
			STARSPEED_LOGO_FLARE_1->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_flare_1.png"));
			STARSPEED_LOGO_FLARE_1->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			STARSPEED_LOGO_FLARE_1->transform()->position.set(1920 * 0.53, 1080 / 11);
			STARSPEED_LOGO_FLARE_1->transform()->scale.set(480 * 2, 480 * 2);
			STARSPEED_LOGO_FLARE_1->transform()->color.set(255, 255, 255, 25);
			STARSPEED_LOGO_FLARE_1->addToCurrentScene();

			StarSpeedLogoTS* STARSPEED_LOGO = new StarSpeedLogoTS();
			STARSPEED_LOGO->SPLASH = SPLASH_TEXT;
			STARSPEED_LOGO->addToCurrentScene();

			Utility::addBackGlow();

			if (!discordApi.isCreated()) {
				SWDAvatar* SWD_AVATAR = new SWDAvatar();
				SWD_AVATAR->addToCurrentScene();
			}

			if (discordApi.isCreated()) {
				discordAvatar->addComponent<Motor::SpriteComponent>(avatarTexture);
				discordAvatar->addToCurrentScene();
			}

            auto* MUSIC_HANDLER = new MusicHandler();
            MUSIC_HANDLER->addToCurrentScene();

            auto debugText = new DebugText(StarSpeed::Tex::DEBUG_FONT, StarSpeed::Tex::DEBUG_FONT_OUTLINE);
            debugText->transform()->depth = 47;
            debugText->addToCurrentScene();
            debugText->transform()->scale.set(32, 48 / 2);
            debugText->coordinateObject = CURSOR;

            auto* TEST = new TestSheet();
            TEST->addToCurrentScene();
        }
	};
}