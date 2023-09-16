#pragma once

#include "motor/content/texture.hpp"
#include "motor/content/font.hpp"

extern std::string SWD_USERNAME;
extern std::string SWD_PASSWORD;
namespace StarSpeed::Tex {
	extern Motor::Texture* SWD_LOGO;
	extern Motor::Texture* SWD_LOGO_WIDE;
	extern Motor::Texture* SWD_LOGO_SQUARE;
	extern Motor::Texture* SWD_LOGO_SQUARE_PIXEL;
	extern Motor::Texture* TEXTFIELD;
	extern Motor::Texture* CIRCLE_GLOW;
	extern Motor::Font* GAME_FONT;
	extern Motor::Font* GAME_FONT_OUTLINE;

	extern Motor::Texture* SAW_ENEMY;
	extern Motor::Texture* CENT_ENEMY;
	extern Motor::Texture* CENT_EXPANDED_ENEMY;
	extern Motor::Texture* CINA_ENEMY;
	extern Motor::Texture* ESENT_ENEMY;
	extern Motor::Texture* FAIRE_ENEMY;
	extern Motor::Texture* PINE_ENEMY;
	extern Motor::Texture* ZENIN_ENEMY;
	extern Motor::Texture* SKRIP_ENEMY;
	extern Motor::Texture* DEFAULT_BULLET;
	extern Motor::Texture* PLAYER_BULLET;
	extern Motor::Texture* ENEMY_BULLET;
	extern Motor::Texture* CENT_BULLET;
	extern Motor::Texture* STAR;
	extern Motor::Texture* SQUARE_ALERT;

	extern Motor::Texture* BUTTON_LONG;
	extern Motor::Texture* BUTTON_LONG_SELECTED;

	extern Motor::Texture* CHECKBOX;
	extern Motor::Texture* CHECKBOX_MARKED;

	extern Motor::Texture* CHECKBOX_SELECTED;
	extern Motor::Texture* CHECKBOX_MARKED_SELECTED;

	extern Motor::Texture* BAR_EMPTY;
	extern Motor::Texture* BAR_FULL;

	extern Motor::Texture* CELL;


	extern Motor::Font* DEBUG_FONT;
	extern Motor::Font* DEBUG_FONT_OUTLINE;
	void setTextures();
}
