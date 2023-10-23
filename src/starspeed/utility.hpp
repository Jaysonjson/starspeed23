#pragma once

#include "motor/object/gameobject.hpp"
#include "motor/components/sprite.hpp"
#include "textures.hpp"
#include "starspeed/components/down_movement.hpp"

namespace StarSpeed::Utility {
	
	inline void addBackGlow() {

        Motor::GameObject* CLOUD_BACKGROUND = new Motor::GameObject();
        Motor::DynamicTexture* CLOUD_BACKGROUND_TEX = new Motor::DynamicTexture(Motor::ResourceLocation(resourcePackMod, "sprites/cloud.png"));
        CLOUD_BACKGROUND_TEX->interpolated_ = true;
        CLOUD_BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(CLOUD_BACKGROUND_TEX);
        CLOUD_BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
        CLOUD_BACKGROUND->transform()->scale.set(4000, 4000);
        CLOUD_BACKGROUND->transform()->position.set(1920 / 2, 0);
        CLOUD_BACKGROUND->transform()->color.setAlpha(12);
        CLOUD_BACKGROUND->addComponent<DownMovementComponent>()->speed_ = 0.04f;
        CLOUD_BACKGROUND->getComponent<DownMovementComponent>()->resetY_ = 2000;
        CLOUD_BACKGROUND->getComponent<DownMovementComponent>()->reset_ = true;
        CLOUD_BACKGROUND->addToCurrentScene();


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
		SUN_GLOW_LEFT->transform()->scale.set(4000, 4000);
		SUN_GLOW_LEFT->transform()->position.set(0 - 750, 0 - 750);
		SUN_GLOW_LEFT->transform()->color.set(214, 134, 54, 190);
		SUN_GLOW_LEFT->addToCurrentScene();


		Motor::GameObject* MIDDLE_GLOW = new Motor::GameObject();
		MIDDLE_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		MIDDLE_GLOW->transform()->scale.set(3000, 3000);
		MIDDLE_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
		MIDDLE_GLOW->transform()->color.set(29, 44, 79, 116);
		MIDDLE_GLOW->addToCurrentScene();

		Motor::GameObject* MIDDLE_GLOW2 = new Motor::GameObject();
		MIDDLE_GLOW2->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		MIDDLE_GLOW2->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		MIDDLE_GLOW2->transform()->scale.set(3000, 3000);
		MIDDLE_GLOW2->transform()->position.set(1920 / 2, 1080 / 2);
		MIDDLE_GLOW2->transform()->color.set(59, 44, 129, 40);
		MIDDLE_GLOW2->addToCurrentScene();

		Motor::GameObject* BACK_GLOW = new Motor::GameObject();
		BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		BACK_GLOW->transform()->scale.set(6000, 6000);
		BACK_GLOW->transform()->position.set(-750, -750);
		BACK_GLOW->transform()->color.set(19, 37, 48, 175);
		BACK_GLOW->addToCurrentScene();

		Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
		BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
		BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
		BACK2_GLOW->transform()->scale.set(6000, 6000);
		BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
		BACK2_GLOW->transform()->color.set(19, 37, 48, 95);
		BACK2_GLOW->addToCurrentScene();

	}

}