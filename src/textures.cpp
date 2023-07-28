#include "starspeed/textures.hpp"
#include "starspeed/resourcepack.hpp"

namespace StarSpeed::Tex {
	Motor::Texture* SWD_LOGO = nullptr;
	Motor::Font* GAME_FONT = nullptr;
	Motor::Font* GAME_FONT_OUTLINE = nullptr;

	void setTextures() {
		SWD_LOGO = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo.png"));
		GAME_FONT = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
		GAME_FONT_OUTLINE = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/yoster.ttf"), 32);
		GAME_FONT_OUTLINE->load();
		GAME_FONT_OUTLINE->setOutline(12);
	}
}