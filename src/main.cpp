#define CURL_STATICLIB
#pragma comment(lib, "libcurl_a.lib")
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "advapi32.lib")

#include "motor/motor.hpp"
#include "motor/paths.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/scenes/splash.hpp"
#include "starspeed/resourcepack.hpp"
#include "starspeed/textures.hpp"
#include "motor/gameobjects/debugtext.hpp"
#include "starspeed/cursor.hpp"
#include "starspeed/profile.hpp"
#include "motor/console/console.hpp"

Motor::Mod* fallbackMod = new Motor::Mod("starspeed");

CursorObject* CURSOR = new CursorObject();

namespace StarSpeed {
	PlayerProfile* playerProfile = new PlayerProfile{};
}

#undef main
int main() {
	Motor::Path::set_save_game_folder("StarSpeed23");
	StarSpeed::Tex::setTextures();
	//getriebe.getConsole()->consoleFont_ = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
	//getriebe.getConsole()->backGround_ = new Motor::SpriteComponent(Motor::ResourceLocation(resourcePackMod, "fall.png"));
	//getriebe.getConsole()->backGround_->transform_ = getriebe.getConsole()->backGroundTransform;
	//getriebe.init("StarSpeed23", 1920 * 0.75, 1080 * 0.75, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
	getriebe.init("StarSpeed23", 1920 * 0.75, 1080 * 0.75, 0, SDL_RENDERER_ACCELERATED);
	StarSpeed::playerProfile->load();
	StarSpeed::addAchievements();
	SDL_Surface* icon = IMG_Load(Motor::ResourceLocation(resourcePackMod, "app/icon.png").getPath().c_str());
	SDL_SetWindowIcon(getriebe.sdl_window(), icon);
	getriebe.getGame()->forceSetScene(new StarSpeed::SplashScene());
	CURSOR->TOOLTIP->addToCurrentScene();
	CURSOR->addToCurrentScene();
	StarSpeed::ACHIEVEMENT_UNLOCK_HEADER->addToCurrentScene();
	auto debugText = new DebugText(StarSpeed::Tex::DEBUG_FONT, StarSpeed::Tex::DEBUG_FONT_OUTLINE);
	debugText->coordinateObject = CURSOR;
	debugText->transform()->depth = 50;
	debugText->addToCurrentScene();
	debugText->transform()->scale.set(28 / 2, 48 / 2);
	while (getriebe.getGame()->running_) {
		getriebe.getGame()->loop();
	}
	StarSpeed::playerProfile->save();
	getriebe.stop();
}