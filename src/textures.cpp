#include "starspeed/textures.hpp"
#include "starspeed/resourcepack.hpp"

namespace StarSpeed::Tex {
	extern Motor::Texture* SWD_LOGO = nullptr;

	void setTextures() {
		SWD_LOGO = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/splash/swd_logo.png"));
	}
}