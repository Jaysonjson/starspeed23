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

	extern Motor::Texture* ENEMY_SHIPS;
	extern Motor::Texture* BULLETS;
	extern Motor::Texture* STAR_SHEET;
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

    extern Motor::Texture* CLOUD;


    extern Motor::Texture* EXPLOSION_SHEET;

    extern Motor::Font* DEBUG_FONT;
	extern Motor::Font* DEBUG_FONT_OUTLINE;
	void setTextures();

    namespace Sheet {

        constexpr int ENEMY_SHIPS_ROW = 3;
        constexpr int ENEMY_SHIPS_COLUMN = 4;

        constexpr int CENT_ROW = 0;
        constexpr int CENT_COLUMN = 0;

        constexpr int CENT_EXPANDED_ROW = 0;
        constexpr int CENT_EXPANDED_COLUMN = 1;

        constexpr int CINA_ROW = 0;
        constexpr int CINA_COLUMN = 2;

        constexpr int ZENIN_ROW = 0;
        constexpr int ZENIN_COLUMN = 3;

        constexpr int SAW_ROW = 2;
        constexpr int SAW_COLUMN = 0;
    }
}
