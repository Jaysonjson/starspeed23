#include "starspeed/textures.hpp"
#include "starspeed/resourcepack.hpp"

std::string SWD_USERNAME = "";
std::string SWD_PASSWORD = "";

namespace StarSpeed::Tex {
	Motor::Texture* SWD_LOGO = nullptr;
	Motor::Texture* TEXTFIELD = nullptr;
	Motor::Font* GAME_FONT = nullptr;
	Motor::Font* GAME_FONT_OUTLINE = nullptr;

	Motor::Font* DEBUG_FONT = nullptr;
	Motor::Font* DEBUG_FONT_OUTLINE = nullptr;

	void setTextures() {
		SWD_LOGO = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo.png"));
		TEXTFIELD = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/login/textfield.png"));
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