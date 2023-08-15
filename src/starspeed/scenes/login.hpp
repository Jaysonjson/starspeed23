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
#include "starspeed/sceneswitcher.hpp"
#include "starspeed/objects/star.hpp"
//WIP
namespace StarSpeed {

	class PasswordTextField : public Motor::GameObject {
	public:


		std::string input = "";
		std::string placeholder = "Password";
		bool activatedField = false;

		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::TEXTFIELD);
			getComponent<Motor::SpriteComponent>()->customColor_.set(255, 255, 255, 175);
			getComponent<Motor::SpriteComponent>()->useCustomColor_ = true;
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::LEFT;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			getComponent<Motor::TextComponentBlended>()->translate_.set(-230, 0);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;

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
			getComponent<Motor::SpriteComponent>()->customColor_.set(255, 255, 255, 175);
			getComponent<Motor::SpriteComponent>()->useCustomColor_ = true;
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent(placeholder);
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::LEFT;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40, 48);
			getComponent<Motor::TextComponentBlended>()->translate_.set(-230, 0);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;
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
			addComponent<Motor::SpriteComponent>(Tex::BUTTON_LONG);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Skip");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40 * 1.35, 48 * 1.35);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-250, 0);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;

			transform()->position.set(1920 / 2, 1080 / 1.3);
			transform()->scale.set(84 * 6, 16 * 6);
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						switchToTitleScreen();
						CURSOR->clickable(false);
					}
				}
				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG_SELECTED);
						CURSOR->clickable(true);
						triggerCursor = true;
					}
					else {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG);
						if (triggerCursor) {
							CURSOR->clickable(false);
							triggerCursor = false;
						}
					}
				}
			}
		};
	};
	class LoginButton;
	static bool validLogin(const std::string& apiUrl, LoginButton* loginButton);

	class LoginButton : public Motor::GameObject {
	public:
		TextField* user;
		PasswordTextField* password;
		std::string loginResponse = "";
		void onCreate() override {
			addComponent<Motor::SpriteComponent>(Tex::BUTTON_LONG);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Login");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40 * 1.35, 48 * 1.35);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-240, 0);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;

			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>(1)->setContent("");
			getComponent<Motor::TextComponentBlended>(1)->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>(1)->customScale_.set(40 * 1.35, 48 * 1.35);
			getComponent<Motor::TextComponentBlended>(1)->translate_.set(0, -250);
			getComponent<Motor::TextComponentBlended>(1)->useCustomScale_ = true;

			transform()->position.set(1920 / 2, 1080 / 1.5);
			transform()->scale.set(84 * 6, 16 * 6);
		}

		void update() override {
			Motor::GameObject::update();
			getComponent<Motor::TextComponentBlended>(1)->setContent(loginResponse);
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						SWD_USERNAME = user->input;
						SWD_PASSWORD = md5(password->input);
						playerProfile->swd_username = SWD_USERNAME;
						playerProfile->swd_password = SWD_PASSWORD;
						if (validLogin(std::string{"http://api.swdteam.com/script/login.php?u=" + SWD_USERNAME + "&p=" + SWD_PASSWORD + "&a=StarSpeed23"}, this)) {
							CURSOR->clickable(false);
							playerProfile->save();
							unlockAchievement(Achmts::LOGIN_SWD);
							switchToTitleScreen();
						}
					}
				}

				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG_SELECTED);
						CURSOR->clickable(true);
						triggerCursor = true;
					}
					else {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG);
						if (triggerCursor) {
							CURSOR->clickable(false);
							triggerCursor = false;
						}
					}
				}
			}
		};
	};

	static bool validLogin(const std::string& apiUrl, LoginButton* loginButton) {
		auto curl = curl_easy_init();
		if (curl) {
			const char* url = apiUrl.c_str();
			curl_easy_setopt(curl, CURLOPT_URL, url);
			std::string response_string;
			curl_slist* headers = NULL;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			response_string = std::regex_replace(response_string, std::regex("\\<pre>"), "");
			response_string = std::regex_replace(response_string, std::regex("\\</pre>"), "");
			nlohmann::json js = nlohmann::json::parse(response_string);
			std::string resp = js["response"];
			if (resp == "Invalid username") {
				loginButton->loginResponse = "Invalid Username";
				return false;
			}

			if (resp == "Incorrect Password") {
				loginButton->loginResponse = "Incorrect Password";
				return false;
			}

			return true;
		}
		else {
			MOTOR_LOG("CURL NOT LOADED");
		}
		return false;
	}

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
			addComponent<Motor::SpriteComponent>(Tex::BUTTON_LONG);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteColliderComponent>();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseClickEvent();
			getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Use Discord instead");
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::MID;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(40 * 0.8, 48 * 0.8);
			//getComponent<Motor::TextComponentBlended>()->translate_.set(-240, 0);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;

			transform()->position.set(1920 / 2, 1080 / 1.1);
			transform()->scale.set(84 * 4, 16 * 4);
			if (!playerProfile->swd_username.empty()) {
				SWD_USERNAME = playerProfile->swd_username;
				SWD_PASSWORD = playerProfile->swd_password;
				switchToTitleScreen();
			}
		}

		bool triggerCursor = false;
		void onComponentEvent(Motor::IComponentEvent* eventData) override {
			if (eventData->id() == "collider") {
				Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						//discordApi.start(903707517236961290, EDiscordCreateFlags::DiscordCreateFlags_NoRequireDiscord);
						//std::thread* discordThread = new std::thread(discordThreadFunction);
						switchToTitleScreen();
					}
				}

				if (colliderEvent->type == Motor::HOVER) {
					if (colliderEvent->onObject) {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG_SELECTED);
						CURSOR->clickable(true);
						triggerCursor = true;
					}
					else {
						getComponent<Motor::SpriteComponent>()->setTexture(Tex::BUTTON_LONG);
						if (triggerCursor) {
							CURSOR->clickable(false);
							triggerCursor = false;
						}
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
			SDL_SetRenderDrawColor(getriebe.sdl_renderer(), 0, 0, 0, 255);

			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist_x(0, 1920);
			std::uniform_real_distribution<double> dist_y(0, 1080);

			for (int i = 0; i < 75; i++) {
				Star* STAR = new Star();
				STAR->transform()->position.set(dist_x(mt), dist_y(mt));
				STAR->transform()->depth = -1;
				STAR->addToCurrentScene(false);
			}

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
			SWD_LOGO->addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO_SQUARE_PIXEL);
			SWD_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			SWD_LOGO->transform()->position.set(1920 / 2, 1080 / 4);
			SWD_LOGO->transform()->scale.set(300);
			SWD_LOGO->addToCurrentScene();
		}
	};
}