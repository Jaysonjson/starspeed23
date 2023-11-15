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

    struct CellData {
        bool unlocked = false;
        bool cleared = false;
        std::string cellId_ = "";
    };

    class CellObject : public Motor::GameObject {
    public:
        bool unlocked = false;
        bool cleared = false;
        PlayerMapShip* player_ = nullptr;
        std::string cellId_ = "";

    public:
        void onCreate() override {
            addComponent<Motor::SpriteComponent>(Tex::CELL);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            transform()->scale.set(cellSize_, cellSize_);
            addComponent<Motor::SpriteColliderComponent>();
            getComponent<Motor::SpriteColliderComponent>()->registerMouseHoverEvent();
        }

        void update() override {
            Motor::GameObject::update();
            if (!unlocked) {
                transform()->color.set(69, 37, 38, 50);
            }
            else {
                transform()->color.set(0, 0, 255, 100);
            }

            if (!unlocked && player_) {
                if (inCoordinate({ player_->transform()->position.fixedScreen().getX(), player_->transform()->position.fixedScreen().getY() })) {
                    unlocked = true;
                    MOTOR_LOG("Player RUID: " + player_->getRUID());
                }
            }
            if (unlocked && player_) {
                const uint8* key = SDL_GetKeyboardState(NULL);
                if (key[SDL_Scancode::SDL_SCANCODE_I]) {
                    if (inCoordinate({ player_->transform()->position.fixedScreen().getX(), player_->transform()->position.fixedScreen().getY() })) {
                        CURSOR->resetTooltip();
                        getriebe.getGame()->switchScene(new FightScene());
                    }
                }
            }
        }

        bool triggerCursor = false;
        void onComponentEvent(Motor::IComponentEvent* eventData) override {
            if (unlocked) {
                if (eventData->id() == "collider") {
                    Motor::ColliderEvent* colliderEvent = dynamic_cast<Motor::ColliderEvent*>(eventData);
                    if (colliderEvent->type == Motor::HOVER) {
                        if (!colliderEvent->onObject) {
                            transform()->scale.set(cellSize_);
                            if (triggerCursor) {
                                CURSOR->resetTooltip();
                                CURSOR->clickable(false);
                                triggerCursor = false;
                            }
                        }
                        else {
                            transform()->scale.set(cellSize_ * 0.9);
                            CURSOR->setTooltip("Sector " + cellId_);
                            CURSOR->clickable(true);
                            triggerCursor = true;
                        }
                    }
                }
            }
        };

        bool inCoordinate(const Motor::Vector2D& vec) {
            Motor::TransformComponent* transformComponent = transform();
            Motor::Scale scale = transformComponent->scale.cameraAdjusted();
            Motor::Vector2D spritePos{ (float)getComponent<Motor::SpriteComponent>()->destRectangle_.x - 1, (float)getComponent<Motor::SpriteComponent>()->destRectangle_.y - 1 };
            Motor::Vector2D endPos{ spritePos.getX() + scale.x, spritePos.getY() + scale.y };
#undef max
#undef min
            if (vec.getX() <= std::max(spritePos.getX(), endPos.getX()) && vec.getX() >= std::min(spritePos.getX(), endPos.getX())
                && vec.getY() <= std::max(spritePos.getY(), endPos.getY()) && vec.getY() >= std::min(spritePos.getY(), endPos.getY())) {
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

            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist_x(0, 1920);
            std::uniform_real_distribution<double> dist_y(0, 1080);

            for (int i = 0; i < 200; i++) {
                Star* STAR = new Star();
                STAR->transform()->position.set(dist_x(mt), dist_y(mt));
                STAR->addToCurrentScene(false);
            }

            PlayerMapShip* player = new PlayerMapShip();
            size_t x_row = 25;
            size_t y_row = 25;
            cellHandler_.cells_.reserve(25 * 25);
            for (size_t i = 0; i < x_row; ++i) {
                for (size_t j = 0; j < y_row; ++j) {
                    CellObject* cell = new CellObject();
                    size_t x_pos = i * cellSize_ + i * cellOffset_;
                    size_t y_pos = j * cellSize_ + j * cellOffset_;
                    cell->cellId_ = std::to_string(i) + "_" + std::to_string(j);
                    cell->transform()->position.set(x_pos, y_pos);
                    cell->player_ = player;
                    cell->addToCurrentScene(false);
                    cellHandler_.cells_.push_back(cell);
                }
            }

            Motor::GameObject* CLOUD_BACKGROUND = new Motor::GameObject();
            CLOUD_BACKGROUND->addComponent<Motor::SpriteComponent>(Tex::CLOUD);
            CLOUD_BACKGROUND->getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_ADD;
            CLOUD_BACKGROUND->transform()->scale.set(2250, 2250);
            CLOUD_BACKGROUND->transform()->position.set(1920 / 2, -2750);
            CLOUD_BACKGROUND->transform()->color.setAlpha(18);
            CLOUD_BACKGROUND->addComponent<DownMovementComponent>()->speed_ = 0.08f;
            CLOUD_BACKGROUND->getComponent<DownMovementComponent>()->resetY_ = 2000;
            CLOUD_BACKGROUND->getComponent<DownMovementComponent>()->reset_ = true;
            CLOUD_BACKGROUND->addToCurrentScene();

            Motor::GameObject* BACKGROUND = new Motor::GameObject();
            Motor::DynamicTexture* BACKGROUND_TEX = new Motor::DynamicTexture(Motor::ResourceLocation(resourcePackMod, "fall.png"));
            BACKGROUND_TEX->interpolated_ = true;
            BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(BACKGROUND_TEX);
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>()->ignoreCamera_ = true;

            BACKGROUND->addComponent<Motor::DynamicSpriteComponent>(Motor::ResourceLocation(resourcePackMod, "sprites/title/starspeed_xr.png"));
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_BLEND;
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->ignoreCamera_ = true;
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->translate_.set(0, -400);
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->useCustomScale_ = true;
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->customScale_.set(76 * 5, 42 * 5);
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->useCustomColor_ = true;
            BACKGROUND->getComponent<Motor::DynamicSpriteComponent>(1)->customColor_.set(255, 255, 255, 255);

            BACKGROUND->transform()->scale.set(240 * 2, 1080);
            BACKGROUND->transform()->position.set(1680, 1080 / 2);
            BACKGROUND->transform()->color.set(6, 6, 28, 255);
            BACKGROUND->addToCurrentScene();

            player->addToCurrentScene();
            Utility::addBackGlow();
            getCamera().reset();
            //getCamera().setTarget(player);
        }
    };
}