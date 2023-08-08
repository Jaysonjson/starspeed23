#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/resourcepack.hpp"
#include "login.hpp"
#include "starspeed/textures.hpp"
#include "starspeed/objects/ships/player.hpp"
#include "starspeed/objects/enemy_spawner.hpp"

namespace StarSpeed {

	class ProgressText : public Motor::GameObject {
	public:
		int* progress;
		
		void onCreate() override {
			addComponent<Motor::TextComponentBlended>(Tex::GAME_FONT);
			getComponent<Motor::TextComponentBlended>()->setContent("Among Us");
			getComponent<Motor::TextComponentBlended>()->ignoreCamera_ = true;
			transform()->position.set(1680, 300);
			transform()->scale.set(32, 32);
		}

		void update() override {
			Motor::GameObject::update();
			getComponent<Motor::TextComponentBlended>()->setContent("Progress: " + std::to_string(*progress) + "%");
		}
	};


	class FightScene : public Motor::Scene {
		int progress_ = 0;
		void init(Motor::Game* game) {
			Motor::Scene::init(game);

			Motor::GameObject* CLOUD_BACKGROUND = new Motor::GameObject();
			CLOUD_BACKGROUND->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/cloud.png"));
			CLOUD_BACKGROUND->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			CLOUD_BACKGROUND->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			CLOUD_BACKGROUND->transform()->scale.set(5000, 9000);
			CLOUD_BACKGROUND->transform()->position.set(1920 / 2, -1750);
			CLOUD_BACKGROUND->transform()->color.setAlpha(8);
			CLOUD_BACKGROUND->addComponent<DownMovementComponent>()->speed_ = 0.04f;
			CLOUD_BACKGROUND->addToCurrentScene();

			PlayerShip* PLAYER_SHIP = new PlayerShip();
			PLAYER_SHIP->progress_ = &progress_;
			PLAYER_SHIP->addToCurrentScene();
			
			Motor::GameObject* BACKGROUND = new Motor::GameObject();
			BACKGROUND->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "fall.png"));
            BACKGROUND->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			BACKGROUND->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;

			BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed.png"));
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->ignoreCamera_ = true;
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->translate_.set(0, -400);
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->useCustomScale_ = true;
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->customScale_.set(76 * 5, 42 * 5);
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->useCustomColor_ = true;
			BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->customColor_.set(255, 255, 255, 255);

            BACKGROUND->transform()->scale.set(240 * 2, 1080);
            BACKGROUND->transform()->position.set(1680, 1080 / 2);
			BACKGROUND->transform()->color.set(6, 6, 28, 200);
			BACKGROUND->addToCurrentScene();

			getCamera().setTarget(PLAYER_SHIP);
			getCamera().enableX = false;

			EnemySpawner* ENEMY_SPAWNER = new EnemySpawner();
			ENEMY_SPAWNER->PLAYER = PLAYER_SHIP;
			ENEMY_SPAWNER->addToCurrentScene();

			Motor::GameObject* SUN_GLOW = new Motor::GameObject();
			SUN_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
            SUN_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			SUN_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			SUN_GLOW->transform()->scale.set(5000, 5000);
			SUN_GLOW->transform()->position.set(1920 + 1200, 1080 + 1200);
			SUN_GLOW->transform()->color.set(214, 134, 54, 175);
			SUN_GLOW->addToCurrentScene();

			Motor::GameObject* MIDDLE_GLOW = new Motor::GameObject();
			MIDDLE_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			MIDDLE_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			MIDDLE_GLOW->transform()->scale.set(5000, 5000);
			MIDDLE_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			MIDDLE_GLOW->transform()->color.set(29, 44, 79, 100);
			MIDDLE_GLOW->addToCurrentScene();

			Motor::GameObject* BACK_GLOW = new Motor::GameObject();
			BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK_GLOW->transform()->scale.set(5000, 4000);
			BACK_GLOW->transform()->position.set(-750, -750);
			BACK_GLOW->transform()->color.set(19, 37, 48, 175);
			BACK_GLOW->addToCurrentScene();

			Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
			BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK2_GLOW->transform()->scale.set(5000, 4000);
			BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			BACK2_GLOW->transform()->color.set(19, 37, 48, 50);
			BACK2_GLOW->addToCurrentScene();

			ProgressText* PROGRESS_TEXT = new ProgressText();
			PROGRESS_TEXT->progress = &progress_;
			PROGRESS_TEXT->addToCurrentScene();

		}
	};
}