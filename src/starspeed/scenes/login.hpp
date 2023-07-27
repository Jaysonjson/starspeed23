#pragma once
#include "motor/object/scene.hpp"
#include "motor/components/sprite.hpp"
namespace StarSpeed {
	class LoginScreen : public Motor::Scene {

	public:
		void init(Motor::Game* game) override {
			Motor::Scene::init(game);
		}
	};
}