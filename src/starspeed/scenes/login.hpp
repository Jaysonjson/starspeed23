#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/components/text.hpp"
#include "starspeed/textures.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/resourcepack.hpp"
#include "titlescreen.hpp"
#include "starspeed/objects/swdavatar.hpp"
#include "starspeed/cursor.hpp"
#include "starspeed/discord.hpp"
#include "starspeed/profile.hpp"
//WIP
namespace StarSpeed {

	class PasswordTextField : public Motor::GameObject {
	public:


		std::string input = "";
		std::string placeholder = "Password";
		bool activatedField = false;

		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::LEFT;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			getComponent<Motor::TextComponentBlended>()->translate_.set(-230, 0);

			transform()->position.set(1920 / 2, 1080 / 1.75);
			transform()->scale.set(500, 64);
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						activatedField = !activatedField;
						if (activatedField) {
							startTextInput();
						}
						else {
							stopTextInput();
						}
					}
				}
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->color.set(255, 255, 255, 255);
						CURSOR->clickable(false);
					}
					else {
						transform()->color.set(125, 50, 90, 255);
						CURSOR->clickable(true);
					}
				}
			}
		};
#
		void update() override {
			Motor::GameObject::update();
			if (activatedField) {
				transform()->color.set(125, 125, 90, 255);
			}
			else {
				transform()->color.set(255, 255, 255, 255);
			}
		}

		void registerEvents() override {
			registerEvent(Motor::Events::keyUp.attach(&onKeyUp));
			registerEvent(Motor::Events::textInput.attach(&onTextInput));
		}

		std::function<void(SDL_Event&)> onKeyUp = [this](SDL_Event& event) {
			if (activatedField && event.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE) {
				if (!input.empty()) {
					input = std::string{ input.begin(), input.end() - 1 };
				}
			}
			if (event.key.keysym.sym == SDL_KeyCode::SDLK_RETURN) {
				activatedField = false;
				stopTextInput();
			}
			if (!input.empty()) {
				std::string fakePW = "";
				for (int i = 0; i < input.size(); ++i) {
					fakePW += "*";
				}
				getComponent<Motor::TextComponentBlended>()->setContent(fakePW);
			}
			else {
				getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
			}
		};

		std::function<void(SDL_Event&)> onTextInput = [this](SDL_Event& event) {
			if (activatedField) {
				input += event.text.text;
				if (!input.empty()) {
					std::string fakePW = "";
					for (int i = 0; i < input.size(); ++i) {
						fakePW += "*";
					}
					getComponent<Motor::TextComponentBlended>()->setContent(fakePW);
				}
				else {
					getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
				}
			}
		};
	};


	class TextField : public Motor::GameObject {
	public:


		std::string input = "";
		std::string placeholder = "Username";
		bool activatedField = false;

		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::LEFT;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			getComponent<Motor::TextComponentBlended>()->translate_.set(-230, 0);
			getComponent<Motor::TextComponentBlended>()->color_.set(87, 86, 85, 15);
			getComponent<Motor::TextComponentBlended>()->useTransformColor_ = false;
			transform()->position.set(1920 / 2, 1080 / 2);
			transform()->scale.set(500, 64);
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						activatedField = !activatedField;
						if (activatedField) {
							startTextInput();
						}
						else {
							stopTextInput();
						}
					}
				}
				if (colliderEvent->type == Motor::HOVER) {
					if (!colliderEvent->onObject) {
						transform()->color.set(255, 255, 255, 255);
						CURSOR->clickable(false);
					}
					else {
						transform()->color.set(125, 50, 90, 255);
						CURSOR->clickable(true);
					}
				}
			}
		};
#
		void update() override {
			Motor::GameObject::update();
			if (activatedField) {
				transform()->color.set(125, 125, 90, 255);
			}
			else {
				transform()->color.set(255, 255, 255, 255);
			}
		}

		void registerEvents() override {
			registerEvent(Motor::Events::keyUp.attach(&onKeyUp));
			registerEvent(Motor::Events::textInput.attach(&onTextInput));
		}

		std::function<void(SDL_Event&)> onKeyUp = [this](SDL_Event& event) {
			if (activatedField && event.key.keysym.sym == SDL_KeyCode::SDLK_BACKSPACE) {
				if (!input.empty()) {
					input = std::string{ input.begin(), input.end() - 1 };
				}
			}
			if (event.key.keysym.sym == SDL_KeyCode::SDLK_RETURN) {
				activatedField = false;
				stopTextInput();
			}
			if (!input.empty()) {
				getComponent<Motor::TextComponentBlended>()->setContent(input);
				getComponent<Motor::TextComponentBlended>()->useTransformColor_ = true;
			}
			else {
				getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
				getComponent<Motor::TextComponentBlended>()->useTransformColor_ = false;
			}
		};

		std::function<void(SDL_Event&)> onTextInput = [this](SDL_Event& event) {
			if (activatedField) {
				input += event.text.text;
				if (!input.empty()) {
					getComponent<Motor::TextComponentBlended>()->setContent(input);
					getComponent<Motor::TextComponentBlended>()->useTransformColor_ = true;
				}
				else {
					getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
					getComponent<Motor::TextComponentBlended>()->useTransformColor_ = false;
				}
			}
		};
	};

	class SkipButton : public Motor::GameObject {
	public:
		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Skip");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-250, 0);

			transform()->position.set(1920 / 2, 1080 / 1.2);
			transform()->scale.set(500, 64);
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						getriebe.getGame()->switchScene(new TitleScreen());
					}
				}
				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						transform()->color.set(125, 125, 90, 255);
						CURSOR->clickable(true);
					}
					else {
						transform()->color.set(255, 255, 255, 255);
						CURSOR->clickable(false);
					}
				}
			}
		};
	};

	class LoginButton : public Motor::GameObject {
	public:
		TextField* user;
		PasswordTextField* password;
		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Login");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-240, 0);

			transform()->position.set(1920 / 2, 1080 / 1.3);
			transform()->scale.set(500, 64);
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						SWD_USERNAME = user->input;
						SWD_PASSWORD = md5(password->input);
						unlockAchievement(Achmts::LOGIN_SWD);
						getriebe.getGame()->switchScene(new TitleScreen());
						playerProfile->swd_username = SWD_USERNAME;
						playerProfile->swd_password = SWD_PASSWORD;
						playerProfile->save();
					}
				}

				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						transform()->color.set(125, 125, 90, 255);
						CURSOR->clickable(true);
					}
					else {
						transform()->color.set(255, 255, 255, 255);
						CURSOR->clickable(false);
					}
				}
			}
		};
	};

/*void discordThreadFunction() {
	bool discordRunning = true;
	if (!avatarTexture->exists()) avatarTexture->load();
	discordAvatar->getComponent<Motor::SpriteComponent>()->setTexture(avatarTexture);
	while (discordRunning) {
		int tries = 0;

		while (discordApi.getCurrentUser().GetId() == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			if (discordApi.getCurrentUser().GetId() != 0) {
				json rawData = discordApi.getUserRawData(discordApi.getCurrentUser().GetId(), "OTAzNzA3NTE3MjM2OTYxMjkw.G1G1i1.KQp3ASBp1d04fy3UM_95e_wYFiaJY6fLDW611k");
				string avatar = discordApi.getAvatarId(rawData);
				auto avatarStream = ifstream{ "avatar.png" };
				bool avatarExists = avatarStream.good();
				avatarStream.close();
				if (!avatarExists) {
					if (discordApi.saveAvatar(rawData, "avatar.png", 512)) MOTOR_LOG("Got Avatar!");
				}
				if (!avatarTexture->exists()) avatarTexture->load();
				MOTOR_LOG("Got Data! " + to_string(discordApi.getCurrentUser().GetId()));
				discordRunning = false;

				rawData = discordApi.getUserRawData(583352965427888134L, "OTAzNzA3NTE3MjM2OTYxMjkw.G1G1i1.KQp3ASBp1d04fy3UM_95e_wYFiaJY6fLDW611k");
				avatar = discordApi.getAvatarId(rawData);
				avatarStream = ifstream{ "avatar2.png" };
				avatarExists = avatarStream.good();
				avatarStream.close();
				if (!avatarExists) {
					if (discordApi.saveAvatar(rawData, "avatar2.png", 512)) MOTOR_LOG("Got Avatar!");
				}
				break;
			}
			++tries;
			MOTOR_LOG("Trying to get Discord Data... [" + to_string(tries) + "/45]");
			if (tries == 45) {
				MOTOR_LOG("Could not get Discord Data!");
				discordRunning = false;
				break;
			}
		}
	}
}
*/
	class DiscordButton : public Motor::GameObject {
	public:
	
		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Use Discord instead");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-240, 0);

			transform()->position.set(1920 / 2, 1080 / 1.1);
			transform()->scale.set(500, 64);
			if (!playerProfile->swd_username.empty()) {
				SWD_USERNAME = playerProfile->swd_username;
				SWD_PASSWORD = playerProfile->swd_password;
				getriebe.getGame()->switchScene(new TitleScreen());
			}
		}

		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						//discordApi.start(903707517236961290, EDiscordCreateFlags::DiscordCreateFlags_NoRequireDiscord);
						//std::thread* discordThread = new std::thread(discordThreadFunction);
						getriebe.getGame()->switchScene(new TitleScreen());
					}
				}

				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						transform()->color.set(125, 125, 90, 255);
						CURSOR->clickable(true);
					}
					else {
						transform()->color.set(255, 255, 255, 255);
						CURSOR->clickable(false);
					}
				}
			}
		};
	};

	class LoginScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
			ACHIEVEMENT_UNLOCK_HEADER->trigger = false;
			Motor::Scene::init(game);

			TextField* USERNAME_FIELD = new TextField();
			USERNAME_FIELD->addToCurrentScene();

			PasswordTextField* PASSWORD_FIELD = new PasswordTextField();
			PASSWORD_FIELD->addToCurrentScene();

			SkipButton* SKIP_BUTTON = new SkipButton();
			SKIP_BUTTON->addToCurrentScene();

			LoginButton* LOGIN_BUTTON = new LoginButton();
			LOGIN_BUTTON->user = USERNAME_FIELD;
			LOGIN_BUTTON->password = PASSWORD_FIELD;
			LOGIN_BUTTON->addToCurrentScene();

			DiscordButton* DISCORD_BUTTON = new DiscordButton();
			DISCORD_BUTTON->addToCurrentScene();

			Motor::GameObject* SWD_LOGO = new Motor::GameObject();
			SWD_LOGO->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/login/swd.png"));
			SWD_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			SWD_LOGO->transform()->position.set(1920 / 2, 1080 / 4);
			SWD_LOGO->transform()->scale.set(300);
			SWD_LOGO->addToCurrentScene();
		}
	};
}