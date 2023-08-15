#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/resourcepack.hpp"
#include "login.hpp"
#include "starspeed/textures.hpp"
#include "starspeed/achievements.hpp"

namespace StarSpeed {

	class SWDLogo : public Motor::GameObject {
	public:

		void onCreate() {
			Tex::SWD_LOGO->load();
			addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 2, 1080 / 2);
			transform()->scale.set(64 * 14, 64 * 14);
		}

		int alpha = 0;
		void fixedUpdate() override {
			Motor::GameObject::fixedUpdate();
			alpha += 2;
			transform()->color.setAlpha(alpha);
			if (alpha > 255) {
				getriebe.getGame()->switchScene(new LoginScreen());
			}
		}
	};

	class SplashScene : public Motor::Scene {
		void init(Motor::Game* game) {
			Motor::Scene::init(game);
			SDL_SetRenderDrawColor(getriebe.sdl_renderer(), 50, 43, 56, 255);
			SWDLogo* swdLogo = new SWDLogo();
			swdLogo->addToCurrentScene();
			unlockAchievement(Achmts::START_GAME);
		}
	};
}