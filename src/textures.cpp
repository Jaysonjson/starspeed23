#include "starspeed/textures.hpp"
#include "starspeed/resourcepack.hpp"

std::string SWD_USERNAME = "";
std::string SWD_PASSWORD = "";

namespace StarSpeed::Tex {
	Motor::Texture* SWD_LOGO = nullptr;
	Motor::Texture* TEXTFIELD = nullptr;
	Motor::Texture* CIRCLE_GLOW = nullptr;
	Motor::Texture* SAW_ENEMY = nullptr;
	Motor::Texture* CENT_ENEMY = nullptr;
	Motor::Texture* CENT_EXPANDED_ENEMY = nullptr;
	Motor::Texture* CINA_ENEMY = nullptr;
	Motor::Texture* ESENT_ENEMY = nullptr;
	Motor::Texture* FAIRE_ENEMY = nullptr;
	Motor::Texture* PINE_ENEMY = nullptr;
	Motor::Texture* SKRIP_ENEMY = nullptr;
	Motor::Texture* ZENIN_ENEMY = nullptr;
	Motor::Texture* DEFAULT_BULLET = nullptr;
	Motor::Texture* BAR_EMPTY = nullptr;
	Motor::Texture* BAR_FULL = nullptr;
	Motor::Font* GAME_FONT = nullptr;
	Motor::Font* GAME_FONT_OUTLINE = nullptr;

	Motor::Font* DEBUG_FONT = nullptr;
	Motor::Font* DEBUG_FONT_OUTLINE = nullptr;

	void setTextures() {
		SWD_LOGO = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo.png"));
		CIRCLE_GLOW = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/circle_glow.png"));
		SAW_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/saw.png"));
		CENT_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/cent.png"));
		CENT_EXPANDED_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/cent_expanded.png"));
		CINA_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/cina.png"));
		ESENT_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/esent.png"));
		FAIRE_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/faire.png"));
		PINE_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/pine.png"));
		SKRIP_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/skrip.png"));
		ZENIN_ENEMY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/ships/enemy/zenin.png"));
		DEFAULT_BULLET = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/bullets/bullet.png"));
		TEXTFIELD = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/login/textfield.png"));
		BAR_EMPTY = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/bar/empty.png"));
		BAR_FULL = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/bar/full.png"));
		GAME_FONT = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
		GAME_FONT_OUTLINE = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
		GAME_FONT_OUTLINE->load();
		GAME_FONT_OUTLINE->setOutline(12);

		DEBUG_FONT = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
		DEBUG_FONT_OUTLINE = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
		DEBUG_FONT_OUTLINE->load();
		DEBUG_FONT_OUTLINE->setOutline(12);
	}
}