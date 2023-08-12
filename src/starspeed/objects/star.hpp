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
			sizeCounter = (int)dist(mt);
			transform()->color.set(255, 255, 255, (uint8) alph(mt));
			int size = (int)siz(mt);
			transform()->scale.set(size);
			addComponent<Motor::SpriteComponent>(Tex::STAR);
			getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
			addComponent<Motor::SpriteComponent>(Tex::CIRCLE_GLOW);
			getComponent<Motor::SpriteComponent>(1)->blendMode_ = SDL_BLENDMODE_ADD;
			getComponent<Motor::SpriteComponent>(1)->useCustomScale_ = true;
			getComponent<Motor::SpriteComponent>(1)->customScale_.set(size + 4);
		}

		void fixedUpdate() override {
			++sizeCounterCurrent;
			if (sizeCounterCurrent >= sizeCounter) {
				sizeCounterCurrent = 0;
				resetSizeCounter();
				if (isIncreased) {
					transform()->scale.set(transform()->scale.x / 1.2, transform()->scale.y / 1.2);
				}
				else {
					transform()->scale.set(transform()->scale.x * 1.2, transform()->scale.y * 1.2);
				}
				isIncreased = !isIncreased;
			}
		}

		void resetSizeCounter() {
			std::random_device rd;
			std::mt19937 mt(rd());
			std::uniform_real_distribution<double> dist(25, 80);
			sizeCounter = (int)dist(mt);
		}

		void render() override {
			Motor::GameObject::render();
			float delta = getriebe.getGame()->getDelta().deltaTime;
			if (transform()->position.screen().getY() > 1080) {
				destroy();
			}
		}

	};
}