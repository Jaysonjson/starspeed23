#pragma once

#include "motor/content/texture.hpp"
#include "motor/content/font.hpp"

extern std::string SWD_USERNAME;
extern std::string SWD_PASSWORD;
namespace StarSpeed::Tex {
	extern Motor::Texture* SWD_LOGO;
	extern Motor::Texture* TEXTFIELD;
	extern Motor::Font* GAME_FONT;
	extern Motor::Font* GAME_FONT_OUTLINE;

	extern Motor::Font* DEBUG_FONT;
	extern Motor::Font* DEBUG_FONT_OUTLINE;
	void setTextures();
}
