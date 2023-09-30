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

    constexpr int cellSize_ = 90;
    constexpr int cellOffset_ = 0;

    class CellObject : public Motor::GameObject {
    public:
        bool unlocked = false;
        PlayerMapShip* player_ = nullptr;

    public:
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Tex::CELL);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->scale.set(cellSize_, cellSize_);
        }

        void update() override {
            Motor::GameObject::update();
            if (!unlocked) {
                transform()->color.set(69, 37, 38, 200);
            }
            else {
                transform()->color.set(0, 0, 255, 200);
            }

            if (!unlocked && player_) {
                if (inCoordinate({ player_->transform()->position.fixedScreen().getX(), player_->transform()->position.fixedScreen().getY()})) {
                    unlocked = true;
                }
            }
        }

        bool inCoordinate(const Motor::Vector2D& vec) {
                Motor::TransformComponent* transformComponent = transform();
                    Motor::Scale scale = transformComponent->scale.cameraAdjusted();
                    Motor::Vector2D spritePos{ (float)getComponent<Motor::SpriteComponent>()->destRectangle_.x - 1, (float)getComponent<Motor::SpriteComponent>()->destRectangle_.y - 1 };
                    Motor::Vector2D endPos{ spritePos.getX() + scale.x, spritePos.getY() + scale.y };
#undef max
#undef min
                    if (vec.getX() <= std::max(spritePos.getX(), endPos.getX()) && vec.getX() >= std::min(spritePos.getX(), endPos.getX())
                        && vec.getY() <= std::max(spritePos.getY(), endPos.getY()) && vec.getY() >= std::min(spritePos.getY(), endPos.getY())) {
                        std::cout << "click" << std::endl;
                        return true;
                    }
            return false;
        }
    };

    class CellHandler {
    public:
        std::vector<CellObject*> cells_{};

    public:

        CellObject* getCellInCoordinate(const Motor::Vector2D& vec) {
            for (auto& cell : cells_) {
                if (cell->inCoordinate(vec)) {
                    return cell;
                }
            }
        }
    };

	class CellmapScene : public Motor::Scene {
    public:
        CellHandler cellHandler_{};
		void init(Motor::Game* game) {
			Motor::Scene::init(game);
           
            PlayerMapShip* player = new PlayerMapShip();

            size_t x_row = 25;
            size_t y_row = 25;
            cellHandler_.cells_.reserve(25 * 25);
            for (size_t i = 0; i < x_row; ++i) {
                for (size_t j = 0; j < y_row; ++j) {
                    CellObject* cell = new CellObject();
                    size_t x_pos = i * cellSize_ + i * cellOffset_;
                    size_t y_pos = j * cellSize_ + j * cellOffset_;
                    cell->transform()->position.set(x_pos, y_pos);
                    cell->player_ = player;
                    cell->addToCurrentScene(false);
                    cellHandler_.cells_.push_back(cell);
                }
            }
           
            player->addToCurrentScene();

            getCamera().reset();
            //getCamera().setTarget(player);
		}
	};
}