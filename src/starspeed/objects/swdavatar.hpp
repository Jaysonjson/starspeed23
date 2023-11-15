#pragma once

#include <iostream>
#include <curl/curl.h>
#include "json.hpp"
#include "motor/object/gameobject.hpp"
#include <regex>
#include <algorithm>
#include <random>
#include "motor/paths.hpp"
#include "motor/components/sprite.hpp"
#include "motor/components/text.hpp"
#include "starspeed/resourcepack.hpp"
#include "starspeed/textures.hpp"
#include "starspeed/achievements.hpp"
#include "starspeed/cursor.hpp"

namespace StarSpeed {

	inline size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
		data->append((char*)ptr, size * nmemb);
		return size * nmemb;
	}

	inline size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata) {
		FILE* stream = (FILE*)userdata;
		if (!stream) return 0;
		size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
		return written;
	}

	static nlohmann::json getAPIData(const std::string& apiUrl) {
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
			return nlohmann::json::parse(response_string);
		}
		else {
			MOTOR_LOG("CURL NOT LOADED");
		}
		return nlohmann::json{ "{}" };
	}


	namespace SWD_JSON {
		constexpr static const char* RESPONSE = "response";
		constexpr static const char* USER_ID = "user_id";
		constexpr static const char* USERNAME = "username";
		constexpr static const char* EMAIL = "email";
		constexpr static const char* EMAIL_UPDATES = "email_updates";
		constexpr static const char* ACCOUNT_STAGE = "account_state";
		constexpr static const char* UUID = "uuid";
		constexpr static const char* OWNS_BETA = "owns_beta"; //BOOL
		constexpr static const char* RANK = "rank";
		constexpr static const char* IN_GAME = "ingame"; //BOOL
		constexpr static const char* ACTIVITY = "activity";
		constexpr static const char* STATUS = "status";
		constexpr static const char* IMAGE = "image";
		constexpr static const char* MC_NAME = "mc_name";
		constexpr static const char* SESSION_KEY = "session_key";
	}

	struct SWD_DATA {
	public:
		nlohmann::json rawData;
		std::string username = "StarSpeedster";
		bool hasBeta = false;
		std::string rank = "Default User";
		std::string imageURL = "";
		void get(std::string username, std::string password) {
			rawData = getAPIData(std::string{"http://api.swdteam.com/script/login.php?u=" + username + "&p=" + password + "&a=StarSpeed23"});
			if (rawData.contains(SWD_JSON::USERNAME)) {
				this->username = rawData[SWD_JSON::USERNAME];
				this->imageURL = "https://swdteam.com/img/uploads/" + this->username + ".png";
			}
			if (rawData.contains(SWD_JSON::OWNS_BETA)) this->hasBeta = rawData[SWD_JSON::OWNS_BETA];
			if (rawData.contains(SWD_JSON::RANK)) this->rank = rawData[SWD_JSON::RANK];
		}

		bool downloadImage() {
			FILE* fp = fopen(std::string{Motor::Path::docs + "swd_avatar.png"}.c_str(), "wb");
			if (!fp) {
				MOTOR_LOG("NO FILE");
				return false;
			}
			if (imageURL.empty()) {
				MOTOR_LOG("EMPTY IMAGE URL");
				return false;
			}
			const char* url = imageURL.c_str();
			auto curl = curl_easy_init();
			if (curl) {
				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackfunction);
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

				CURLcode rc = curl_easy_perform(curl);
				if (rc) {
					MOTOR_LOG(std::to_string(rc));
					MOTOR_LOG("FALSE RC");
					return false;
				}

				long res_code = 0;
				curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res_code);
				if (!((res_code == 200 || res_code == 201) && rc != CURLE_ABORTED_BY_CALLBACK)) {
					MOTOR_LOG(std::to_string(res_code));
					return false;
				}
				curl_easy_cleanup(curl);
			}
			fflush(fp);
			fclose(fp);
			return true;
		}
	};

	struct CustomNameRole {
		std::string nameToOverride = "";
		std::string role_ = "";
		Motor::Color32 roleColor_{};
		Motor::Color32 nameColor_{};
	};

	
	class SWDAvatar : public Motor::GameObject {
	public:

		SWD_DATA swdData{};


        int hueTimer = 0;
        void update() override {
            Motor::GameObject::update();
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0, 255);
            ++hueTimer;
            if(hueTimer == 16) {
                getComponent<Motor::SpriteComponent>(7)->useCustomColor_ = true;
                getComponent<Motor::SpriteComponent>(7)->customColor_.set((int)dist(mt), (int)dist(mt), (int)dist(mt), 255);
                hueTimer = 0;
            }
        }

		void onCreate() {
			std::vector<CustomNameRole> CUSTOM_ROLES{
				{"Joee3", "pissing and shitting and cumming", {}, { 0, 128, 128, 255 }},
				{"Jayson_json", "StarSpeed Developer", {0, 128, 128, 255 }, {0, 128, 128, 255}},
				{ "RedDash16", "", {}, {255, 102, 102, 255}},
				{ "Bug1312", "", {}, {73, 199, 56, 255} },
				{ "Torchwood_one", "Torchwood", {}, {0, 0, 128, 255 }},
				{ "wheezebob", "Weezer ", {74, 26, 110, 255}, {122, 73, 136, 255 } },
                { "Amythical", "Music", {215, 71, 255, 255}, {255, 71, 169, 255 } },
                { "Derpy", "Artist", {215, 71, 255, 255}, {255, 71, 169, 255 } },
                { "Wullfo", "Artist", {215, 71, 255, 255}, {255, 176, 0, 255 } }
            };


			if(!SWD_USERNAME.empty()) {
				swdData.get(SWD_USERNAME, SWD_PASSWORD);
				swdData.downloadImage();
			}
			transform()->position.set(1920 - 200 / 2, 200 / 2);
			transform()->scale.set(155, 155);
			transform()->depth = 30;
			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent(swdData.username);
			getComponent<Motor::TextComponentBlended>()->alignment_ = Motor::TextAlignment::RIGHT;
			getComponent<Motor::TextComponentBlended>()->customScale_.set(24, 24 * 1.25);
			getComponent<Motor::TextComponentBlended>()->translate_.set(-100, -75);
			getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;

			for (CustomNameRole& customRole : CUSTOM_ROLES) {
				if (swdData.username == customRole.nameToOverride) {
					getComponent<Motor::TextComponentBlended>()->color_ = customRole.nameColor_;
					getComponent<Motor::TextComponentBlended>()->useTransformColor_ = false;
					if (!customRole.role_.empty()) {
						swdData.rank = customRole.role_;
					}
					break;
				}
			}

			addComponent<Motor::TextComponentBlended>(Tex::DEBUG_FONT);
			getComponent<Motor::TextComponentBlended>(1)->setContent(swdData.rank);
			getComponent<Motor::TextComponentBlended>(1)->alignment_ = Motor::TextAlignment::RIGHT;
			getComponent<Motor::TextComponentBlended>(1)->customScale_.set(24, 24 * 1.25);
			getComponent<Motor::TextComponentBlended>(1)->translate_.set(-100, -75 + 24 * 1.25);
			getComponent<Motor::TextComponentBlended>(1)->useCustomScale_ = true;

            for (CustomNameRole& customRole : CUSTOM_ROLES) {
                if (swdData.username == customRole.nameToOverride) {
                    getComponent<Motor::TextComponentBlended>(1)->color_ = customRole.roleColor_;
                    getComponent<Motor::TextComponentBlended>(1)->useTransformColor_ = false;
                    break;
                }
            }

			std::ifstream f(Motor::Path::docs + "swd_avatar.png");
			if (f.good()) {
				addComponent<Motor::DynamicSpriteComponent>(Motor::Path::docs + "swd_avatar.png");
				getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			}
			else {
				addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "app/icon.png"));
			}
			addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/trophy.png"));
			getComponent<Motor::SpriteComponent>(1)->translate_.set(-100, -75 + (24 * 1.25) * 2);
			getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(1)->customScale_.set(23, 23);
			getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;

			addComponent<Motor::SpriteComponent>(Tex::BAR_EMPTY);
			getComponent<Motor::SpriteComponent>(2)->translate_.set(-100, -75 + (24 * 1.25) * 4);
			getComponent<Motor::SpriteComponent>(2)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(2)->customScale_.set(10, 75);
			
			addComponent<Motor::SpriteComponent>(Tex::BAR_FULL);
			getComponent<Motor::SpriteComponent>(3)->translate_.set(-100, -75 + (24 * 1.25) * 4);
			getComponent<Motor::SpriteComponent>(3)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(3)->customScale_.set(10, 0);

			if(achievements.size() > 0) {
				float unlockedAchievements = 0;
				for(Achievement* achievement : achievements) {
            		if(achievement->isUnlocked()) {
						++unlockedAchievements;
            		}
        		} 
				if(unlockedAchievements != 0) {
					getComponent<Motor::SpriteComponent>(3)->customScale_.set(10, unlockedAchievements / (float)achievements.size() * 75);
				}
			}


			addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/cell.png"));
			getComponent<Motor::SpriteComponent>(4)->translate_.set(-125, -75 + (24 * 1.25) * 2);
			getComponent<Motor::SpriteComponent>(4)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(4)->customScale_.set(23, 23);
			getComponent<Motor::SpriteComponent>(4)->blendMode_ = SDL_BLENDMODE_BLEND;

			addComponent<Motor::SpriteComponent>(Tex::BAR_EMPTY);
			getComponent<Motor::SpriteComponent>(5)->translate_.set(-125, -75 + (24 * 1.25) * 4);
			getComponent<Motor::SpriteComponent>(5)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(5)->customScale_.set(10, 75);
			
			addComponent<Motor::SpriteComponent>(Tex::BAR_FULL);
			getComponent<Motor::SpriteComponent>(6)->translate_.set(-125, -75 + (24 * 1.25) * 4);
			getComponent<Motor::SpriteComponent>(6)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(6)->customScale_.set(10, 30);

            addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/ui/border/border_0.png"));
            getComponent<Motor::SpriteComponent>(7)->customScale_.set(190, 190);
            getComponent<Motor::SpriteComponent>(7)->useCustomScale_ = true;
            getComponent<Motor::SpriteComponent>(7)->blendMode_ = SDL_BLENDMODE_BLEND;

			//getComponent<Motor::SpriteComponent>(2)->customAngle_ = 90;
			//getComponent<Motor::SpriteComponent>(2)->center_ = SDL_Point{(int)(500 * 0.15f) / 2, 0};
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
						if (triggerCursor) {
							CURSOR->resetTooltip();
							CURSOR->clickable(false);
							triggerCursor = false;
							//getComponent<Motor::DynamicSpriteComponent>()->setTexture(DEFAULT);
						}
					}
					else {
						CURSOR->setTooltip("Open SWD Profile in Browser");
						CURSOR->clickable(true);
						triggerCursor = true;
						//getComponent<Motor::DynamicSpriteComponent>()->setTexture(DEFAULT);
					}
				}
				if (colliderEvent->type == Motor::CLICK) {
					if (colliderEvent->onObject) {
						CURSOR->resetTooltip();
						CURSOR->clickable(false);
						Fuchs::Utility::openURLInBrowser("https://swdteam.com/profile/" + swdData.username);
					}
				}
			}
		};
	};
}