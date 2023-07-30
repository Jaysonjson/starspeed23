#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/components/text.hpp"
#include "starspeed/textures.hpp"
#include "motor/components/collider.hpp"
#include "starspeed/resourcepack.hpp"
#include "titlescreen.hpp"
#include "starspeed/objects/swdavatar.hpp"
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
					}
					else {
						transform()->color.set(125, 50, 90, 255);
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
					}
					else {
						transform()->color.set(125, 50, 90, 255);
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
					}
					else {
						transform()->color.set(255, 255, 255, 255);
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
						SWD_PASSWORD = password->input;
						getriebe.getGame()->switchScene(new TitleScreen());
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
					}
					else {
						transform()->color.set(255, 255, 255, 255);
					}
				}
			}
		};
	};




	class LoginScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
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