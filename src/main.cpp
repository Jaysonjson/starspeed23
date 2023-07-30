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

Motor::Mod* fallbackMod = new Motor::Mod("starspeed");

class CursorObject : public Motor::GameObject {
public:

	void onCreate() {
		persistent_ = true;
	}

	void registerEvents() override {
		registerEvent(Motor::Events::mouseMotion.attach(&onMouse));
	}

	std::function<void(SDL_Event&)> onMouse = [this](SDL_Event& event) {
		getComponent<Motor::TransformComponent>()->position.set(event.button.x, event.button.y);
	};
};


#undef main
int main() {
	Motor::Path::set_save_game_folder("StarSpeed23");
	getriebe.init("StarSpeed2023", 1920, 1080, SDL_WINDOW_RESIZABLE, SDL_RENDERER_ACCELERATED);
	SDL_Surface* icon = IMG_Load(Motor::ResourceLocation(resourcePackMod, "app/icon.png").getPath().c_str());
	SDL_SetWindowIcon(getriebe.sdl_window(), icon);
	StarSpeed::Tex::setTextures();
	getriebe.getGame()->forceSetScene(new StarSpeed::SplashScene());
	auto cursor = new CursorObject();
	cursor->addToCurrentScene();
	auto debugText = new DebugText(StarSpeed::Tex::DEBUG_FONT, StarSpeed::Tex::DEBUG_FONT_OUTLINE);
	debugText->isPersistent();
	debugText->coordinateObject = cursor;
	debugText->transform()->depth = 50;
	debugText->addToCurrentScene();
	debugText->transform()->scale.set(28 / 2, 48 / 2);
	while (getriebe.getGame()->running_) {
		getriebe.getGame()->loop();
	}
	getriebe.stop();
}