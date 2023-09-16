#pragma once

#include "motor/object/gameobject.hpp"
#include "motor/components/sprite.hpp"
#include "textures.hpp"

namespace StarSpeed::Utility {
	
	inline void addBackGlow() {
		Motor::GameObject* SUN_GLOW = new Motor::GameObject();
		SUN_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		SUN_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		SUN_GLOW->transform()->scale.set(5200, 5200);
		SUN_GLOW->transform()->position.set(1920 + 1200, 1080 + 1200);
		SUN_GLOW->transform()->color.set(214, 134, 54, 190);
		SUN_GLOW->addToCurrentScene();

		Motor::GameObject* SUN_GLOW_LEFT = new Motor::GameObject();
		SUN_GLOW_LEFT->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		SUN_GLOW_LEFT->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		SUN_GLOW_LEFT->transform()->scale.set(2000, 2000);
		SUN_GLOW_LEFT->transform()->position.set(0 - 750, 0 - 750);
		SUN_GLOW_LEFT->transform()->color.set(214, 134, 54, 190);
		SUN_GLOW_LEFT->addToCurrentScene();


		Motor::GameObject* MIDDLE_GLOW = new Motor::GameObject();
		MIDDLE_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		MIDDLE_GLOW->transform()->scale.set(5000, 5000);
		MIDDLE_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
		MIDDLE_GLOW->transform()->color.set(29, 44, 79, 126);
		MIDDLE_GLOW->addToCurrentScene();

		Motor::GameObject* BACK_GLOW = new Motor::GameObject();
		BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		BACK_GLOW->transform()->scale.set(5000, 4000);
		BACK_GLOW->transform()->position.set(-750, -750);
		BACK_GLOW->transform()->color.set(19, 37, 48, 175);
		BACK_GLOW->addToCurrentScene();

		Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
		BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		BACK2_GLOW->transform()->scale.set(5000, 4000);
		BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
		BACK2_GLOW->transform()->color.set(19, 37, 48, 95);
		BACK2_GLOW->addToCurrentScene();

	}

}