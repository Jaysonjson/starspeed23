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

	class FightScene : public Motor::Scene {
		void init(Motor::Game* game) {
			Motor::Scene::init(game);
			PlayerShip* PLAYER_SHIP = new PlayerShip();
			PLAYER_SHIP->addToCurrentScene();

			Motor::GameObject* BACKGROUND = new Motor::GameObject();
			BACKGROUND->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "fall.png"));
            BACKGROUND->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			BACKGROUND->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
            BACKGROUND->transform()->scale.set(240 * 2, 1080);
            BACKGROUND->transform()->position.set(1680, 1080 / 2);
			BACKGROUND->transform()->color.set(41, 37, 37, 200);
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
			SUN_GLOW->transform()->scale.set(7000, 7000);
			SUN_GLOW->transform()->position.set(1920 + 1200, 1080 + 1200);
			SUN_GLOW->transform()->color.set(214, 134, 54, 175);
			SUN_GLOW->addToCurrentScene();

			Motor::GameObject* BACK_GLOW = new Motor::GameObject();
			BACK_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK_GLOW->transform()->scale.set(5000, 5000);
			BACK_GLOW->transform()->position.set(-750, -750);
			BACK_GLOW->transform()->color.set(19, 37, 48, 175);
			BACK_GLOW->addToCurrentScene();

			Motor::GameObject* BACK2_GLOW = new Motor::GameObject();
			BACK2_GLOW->addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
			BACK2_GLOW->getComponent<Motor::SpriteComponent>()->ignoreCamera_ = true;
			BACK2_GLOW->transform()->scale.set(5000, 5000);
			BACK2_GLOW->transform()->position.set(1920 / 2, 1080 / 2);
			BACK2_GLOW->transform()->color.set(19, 37, 48, 50);
			BACK2_GLOW->addToCurrentScene();
		}
	};
}