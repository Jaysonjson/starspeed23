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
#include "fuchslib/key.hpp"
#include "starspeed/init/objects.hpp"
#include "starspeed/splashs.hpp"
#include "motor/sound/sound.hpp"

Motor::Mod* fallbackMod = new Motor::Mod("starspeed");

CursorObject* CURSOR = new CursorObject();

namespace StarSpeed {
	PlayerProfile* playerProfile = new PlayerProfile{};
    GameSettings* gameSettings = new GameSettings{};
}

#undef main
int main() {
	Motor::Path::set_save_game_folder("StarSpeed23");
	//getriebe.getConsole()->consoleFont_ = new Motor::Font(Motor::ResourceLocation(resourcePackMod, "fonts/signika.ttf"), 32);
	//getriebe.getConsole()->backGround_ = new Motor::SpriteComponent(Motor::ResourceLocation(resourcePackMod, "fall.png"));
	//getriebe.getConsole()->backGround_->transform_ = getriebe.getConsole()->backGroundTransform;
	//getriebe.init("StarSpeed23", 1920 * 0.75, 1080 * 0.75, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	getriebe.init("StarSpeed23", 1920 * 0.75, 1080 * 0.75, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
	getriebe.getGame()->setTextFPS(12);
    StarSpeed::Tex::setTextures();
	StarSpeed::playerProfile->load();
    StarSpeed::gameSettings->load();
	StarSpeed::addAchievements();
    //SDL_Surface* icon = IMG_Load(Motor::ResourceLocation(resourcePackMod, "app/icon.png").getPath().c_str());
    SDL_Surface* icon = IMG_Load(Motor::ResourceLocation(resourcePackMod, "/app/icon.png").getPath().c_str());
    SDL_SetWindowIcon(getriebe.sdl_window(), icon);

	getriebe.getGame()->forceSetScene(new StarSpeed::SplashScene());

    //auto debugText = new DebugText(StarSpeed::Tex::DEBUG_FONT, StarSpeed::Tex::DEBUG_FONT_OUTLINE);
    ////debugText->transform()->depth = 47;
    //debugText->addToCurrentScene();
    //debugText->transform()->scale.set(28, 48 / 2);

	CURSOR->TOOLTIP->addToCurrentScene();
	CURSOR->addToCurrentScene();
    //debugText->coordinateObject = CURSOR;
    StarSpeed::ACHIEVEMENT_UNLOCK_HEADER->addToCurrentScene();
	SDL_AudioSpec want;
	SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	want.freq = 48000;
	want.format = SDL_AUDIO_F32LE;
	want.channels = 2;

    Mix_OpenAudio(0, &want);
    while (getriebe.getGame()->running_) {
		//debugText->transform()->scale.set(28, 48 / 2);
		getriebe.getGame()->loop();
	}
	StarSpeed::playerProfile->save();
    StarSpeed::gameSettings->save();
	Mix_CloseAudio();
	getriebe.stop();
}