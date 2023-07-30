#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/resourcepack.hpp"
#include "login.hpp"
#include "starspeed/textures.hpp"
#include "starspeed/objects/ships/player.hpp"

namespace StarSpeed {

	class FightScene : public Motor::Scene {
		void init(Motor::Game* game) {
			Motor::Scene::init(game);
			PlayerShip* PLAYER_SHIP = new PlayerShip();
			PLAYER_SHIP->addToCurrentScene();

			Motor::GameObject* BACKGROUND = new Motor::GameObject();
			BACKGROUND->addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "fall.png"));
            BACKGROUND->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            BACKGROUND->transform()->scale.set(240 * 2, 1080);
            BACKGROUND->transform()->position.set(1680, 1080 / 2);
			BACKGROUND->transform()->color.set(41, 37, 37, 200);
			BACKGROUND->addToCurrentScene();
		}
	};
}