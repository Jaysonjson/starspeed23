#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
#include "motor/object/gameobject.hpp"
#include "motor/content/resourcelocation.hpp"
#include "starspeed/resourcepack.hpp"
#include "login.hpp"
#include "starspeed/textures.hpp"
#include "starspeed/achievements.hpp"
#include "starspeed/objects/player_map.hpp"

namespace StarSpeed {

    constexpr int cellSize_ = 80;
    constexpr int cellOffset_ = 4;

    class CellObject : public Motor::GameObject {
        public:
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Tex::CELL);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->scale.set(cellSize_, cellSize_);
        }
    };

	class CellmapScene : public Motor::Scene {
		void init(Motor::Game* game) {
			Motor::Scene::init(game);

            size_t x_row = 64;
            size_t y_row = 64;
            for (size_t i = 0; i < x_row; ++i) {
                for (size_t j = 0; j < y_row; ++j) {
                    CellObject* cell = new CellObject();
                    cell->transform()->position.set(i * cellSize_ + i * cellOffset_, j * cellSize_ + j * cellOffset_);
                    cell->addToCurrentScene(false);
                }
            }
            
			PlayerMapShip* player = new PlayerMapShip();
            player->addToCurrentScene();
            getCamera().reset();
            //getCamera().setTarget(player);
		}
	};
}