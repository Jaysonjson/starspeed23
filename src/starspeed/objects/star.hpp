#pragma once
#include "motor/object/gameobject.hpp"
#include <random>
#include "motor/components/sprite.hpp"
#include "starspeed/textures.hpp"

namespace StarSpeed {
	class Star : public Motor::GameObject {
		int sizeCounter = 0;
		int sizeCounterCurrent = 0;
		bool isIncreased = false;
	public:
		void onCreate() override {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(25, 80);
			std::uniform_real_distribution<double> alph(0, 225);
			std::uniform_real_distribution<double> siz(6, 20);
            std::uniform_int_distribution<int> spr(0, 1);
            sizeCounter = (int)dist(mt);
			transform()->color.set(255, 255, 255, (uint8) alph(mt));
			double size = siz(mt);
			transform()->scale.set(size);
            addComponent<Motor::SpriteSheetComponent>(Tex::STAR_SHEET);
            getComponent<Motor::SpriteSheetComponent>()->setRowColumn(1, 2);
            getComponent<Motor::SpriteSheetComponent>()->selectSprite(spr(mt), 0);
            getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
			getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
            getComponent<Motor::SpriteComponent>(1)->useCustomColor_ = true;
            getComponent<Motor::SpriteComponent>(1)->customColor_.set(255, 255, 255, 50);
		}

		void fixedUpdate() override {
			++sizeCounterCurrent;
			if (sizeCounterCurrent >= sizeCounter) {
				sizeCounterCurrent = 0;
				resetSizeCounter();
				if (isIncreased) {
					transform()->scale.set(transform()->scale.x / 1.25, transform()->scale.y / 1.25);
				}
				else {
					transform()->scale.set(transform()->scale.x * 1.25, transform()->scale.y * 1.25);
                    std::random_device rd;
                    std::mt19937 mt(rd());
                    std::uniform_int_distribution<int> dist(15, 45);
                    sizeCounter = dist(mt);
				}
				isIncreased = !isIncreased;
			}
		}

		void resetSizeCounter() {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(85, 1530);
			sizeCounter = dist(mt);
		}

		void render() override {
			Motor::GameObject::render();
			float delta = getriebe.getGame()->getDelta().deltaTime;
			if (transform()->position.screen().getY() > 1080 * getriebe.getGame()->getRenderer()->widthDifference_) {
				destroy();
			}
		}

	};
}