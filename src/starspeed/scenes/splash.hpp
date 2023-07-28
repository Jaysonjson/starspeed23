#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/resourcepack.hpp"
#include "login.hpp"
#include "starspeed/textures.hpp"

namespace StarSpeed {

	class SWDLogo : public Motor::GameObject {
	public:

		void onCreate() {
			Tex::SWD_LOGO->load();
			addComponent<Motor::SpriteComponent>(Tex::SWD_LOGO);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			transform()->position.set(1920 / 2, 1080 / 2);
			transform()->scale.set(449 * 3, 82 * 3);
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
			SWDLogo* swdLogo = new SWDLogo();
			swdLogo->addToCurrentScene();
		}
	};
}