#include "starspeed/textures.hpp"
#include "starspeed/resourcepack.hpp"

std::string SWD_USERNAME = "";
std::string SWD_PASSWORD = "";

namespace StarSpeed::Tex {
	Motor::Texture* SWD_LOGO = nullptr;
	Motor::Texture* SWD_LOGO_SQUARE = nullptr;
	Motor::Texture* SWD_LOGO_SQUARE_PIXEL = nullptr;
	Motor::Texture* SWD_LOGO_WIDE = nullptr;
	Motor::Texture* TEXTFIELD = nullptr;
	Motor::Texture* CIRCLE_GLOW = nullptr;
    Motor::Texture* ENEMY_SHIPS = nullptr;
	Motor::Texture* BULLETS = nullptr;
	Motor::Texture* BAR_EMPTY = nullptr;
	Motor::Texture* BAR_FULL = nullptr;
    Motor::Texture* STAR_SHEET = nullptr;
    Motor::Texture* BUTTON_LONG = nullptr;
	Motor::Texture* BUTTON_LONG_SELECTED = nullptr;
	Motor::Texture* CHECKBOX = nullptr;
	Motor::Texture* CHECKBOX_MARKED = nullptr;
	Motor::Texture* CHECKBOX_SELECTED = nullptr;
	Motor::Texture* CHECKBOX_MARKED_SELECTED = nullptr;
	Motor::Texture* SQUARE_ALERT = nullptr;
	Motor::Texture* CELL = nullptr;

    Motor::Texture* CLOUD = nullptr;


    Motor::Texture* EXPLOSION_SHEET = nullptr;

	Motor::Font* GAME_FONT = nullptr;
	Motor::Font* GAME_FONT_OUTLINE = nullptr;

	Motor::Font* DEBUG_FONT = nullptr;
	Motor::Font* DEBUG_FONT_OUTLINE = nullptr;

	void setTextures() {
		SWD_LOGO = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo.png"));
		SWD_LOGO_WIDE = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo_wide.png"));
		SWD_LOGO_SQUARE = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "app/icon.png"));
		SWD_LOGO_SQUARE_PIXEL = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/login/swd.png"));
		CIRCLE_GLOW = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/circle_glow.png"));
		CIRCLE_GLOW->interpolated_ = true;
        ENEMY_SHIPS = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/enemy_ships.png"));
		BULLETS = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/bullets.png"));
		TEXTFIELD = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/login/textfield.png"));
		BAR_EMPTY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/bar/empty.png"));
		BAR_FULL = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/bar/full.png"));
		STAR_SHEET = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/background/star_sheet.png"));
        SQUARE_ALERT = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/alert.png"));
        EXPLOSION_SHEET = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "/sprites/explosion_sheet.png"));
		CELL = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/map/cell.png"));
		BUTTON_LONG = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/button.png"));
		BUTTON_LONG_SELECTED = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ui/button_selected.png"));
        CLOUD = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/background/cloud.png"));
        CLOUD->interpolated_ = true;
        BUTTON_LONG_SELECTED->load();
		GAME_FONT = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/xrfont.ttf"), 32);
		GAME_FONT_OUTLINE = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/xrfont.ttf"), 32);
		GAME_FONT_OUTLINE->load();
		GAME_FONT_OUTLINE->setOutline(12);
		DEBUG_FONT = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
		DEBUG_FONT_OUTLINE = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
		DEBUG_FONT_OUTLINE->load();
		DEBUG_FONT_OUTLINE->setOutline(12);

        CLOUD->loadAsThread();
        CIRCLE_GLOW->loadAsThread();
	}
}