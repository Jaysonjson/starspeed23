#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"

namespace StarSpeed {
	class SplashScene : public Motor::Scene {
		void init(Motor::Game* game) {
			Motor::Scene::init(game);
			Motor::GameObject* SWD_LOGO = new Motor::GameObject();
			SWD_LOGO->addComponent<Motor::SpriteComponent>("assets/sprites/splash/swd_logo.png");
			SWD_LOGO->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			SWD_LOGO->getComponent<Motor::TransformComponent>()->position.set(1000, 500);
			SWD_LOGO->getComponent<Motor::TransformComponent>()->scale.set(449 * 3, 82 * 3);
			SWD_LOGO->addToCurrentScene();
		}
	};
}