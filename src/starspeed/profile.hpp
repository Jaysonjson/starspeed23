#pragma once
#include "vector"
#include "string"
#include "json.hpp"
#include "motor/paths.hpp"
#include "fuchslib/encryption/basic.hpp"
#include "mine.hpp"
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>
#define EXTRACT(x, n, J) if (J.contains(n)) x = J[n].get<decltype(x)>()
#define EXTRACT_VAR(x, J) if (J.contains(#x)) x = J[#x].get<decltype(x)>()

namespace StarSpeed {

    inline std::string md5(const std::string& str) {
        unsigned char hash[MD5_DIGEST_LENGTH];
        MD5_CTX md5;
        MD5_Init(&md5);
        MD5_Update(&md5, str.c_str(), str.size());
        MD5_Final(hash, &md5);
        std::stringstream ss;
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return ss.str();
    }


    class PlayerProfile {
        std::vector<std::string> achievements_{};
    public:
        int shipsDestroyed_ = 0;
        //Fuchs::SequencedBasicCryptor basicCryptor{"ahd"};
        std::string swd_username = "";
        std::string swd_password = "";
    public:
        std::vector<std::string>& getAchievements() {
            return achievements_;
        }

        void load() {
            std::ifstream t(Motor::Path::docs + "profile.json");
            if (t.good()) {
                std::stringstream buffer;
                buffer << t.rdbuf();
                if (!nlohmann::json::accept(buffer.str())) return;
                nlohmann::json js = nlohmann::json::parse(buffer.str());
                EXTRACT(achievements_, "achievements", js);
                EXTRACT(shipsDestroyed_, "destroyed_ships", js);
                EXTRACT(swd_username, "usr", js);
                EXTRACT(swd_password, "usrp", js);
                swd_username = mine::Base64::decode(swd_username);
                swd_password = mine::Base64::decode(swd_password);
                MOTOR_LOG("Loaded Player Profile: " + buffer.str())
            }
            else {
                save();
            }
        }

        void save() {
            std::string usernameCache = mine::Base64::encode(swd_username);
            std::string passwordCache = mine::Base64::encode(swd_password);
            nlohmann::json js{{"achievements", achievements_}, { "destroyed_ships", shipsDestroyed_ }, { "usr", usernameCache }, {"usrp", passwordCache }};
            std::ofstream out(Motor::Path::docs + "profile.json");
            out << js;
            MOTOR_LOG("Saved Player Profile");
        }
    };

    class GameSettings {
    public:
        int volume_ = 10;
    public:

        void load() {
            std::ifstream t(Motor::Path::docs + "settings.json");
            if (t.good()) {
                std::stringstream buffer;
                buffer << t.rdbuf();
                if (!nlohmann::json::accept(buffer.str())) return;
                nlohmann::json js = nlohmann::json::parse(buffer.str());
                EXTRACT(volume_, "music_volume", js);
                MOTOR_LOG("Loaded Game Settings: " + buffer.str())
            }
            else {
                save();
            }
        }

        void save() {
            nlohmann::json js{{"music_volume", volume_}};
            std::ofstream out(Motor::Path::docs + "settings.json");
            out << js;
            MOTOR_LOG("Saved Game Settings");
        }
    };

    extern PlayerProfile* playerProfile;
    extern GameSettings* gameSettings;
}