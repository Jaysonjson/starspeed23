#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/md5.h>
#include <curl/curl.h>
#include "json.hpp"
#include "motor/object/gameobject.hpp"
#include <regex>
#include <algorithm>

namespace StarSpeed {

	std::string md5(const std::string& str) {
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

	inline size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
		data->append((char*)ptr, size * nmemb);
		return size * nmemb;
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
		std::string username = "NO USERNAME";
		bool hasBeta = false;
		std::string rank = "NO RANK";
		std::string imageURL = "";
		void get(std::string username, std::string password) {
			rawData = getAPIData(std::string{"http://api.swdteam.com/script/login.php?u=" + username + "&p=" + password + "&a=StarSpeed23"});
			if (rawData.contains(SWD_JSON::USERNAME)) this->username = rawData[SWD_JSON::USERNAME];
			if (rawData.contains(SWD_JSON::OWNS_BETA)) this->hasBeta = rawData[SWD_JSON::OWNS_BETA];
			if (rawData.contains(SWD_JSON::RANK)) this->rank = rawData[SWD_JSON::RANK];
			if (rawData.contains(SWD_JSON::IMAGE)) this->imageURL = rawData[SWD_JSON::IMAGE];
		}
	};

	
	class SWDAvatar : public Motor::GameObject {
	public:
		std::string username = "Jayson_json";
		std::string password = md5("4477xdrt");
		SWD_DATA swdData{};

		void onCreate() {
			swdData.get(username, password);
		}
	};
}