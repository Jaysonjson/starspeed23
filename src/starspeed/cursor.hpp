#pragma once
#include "motor/object/gameobject.hpp"
#include "motor/components/sprite.hpp"

class CursorObject : public Motor::GameObject {
public:

	Motor::Texture* CURSOR_TEX;
	Motor::Texture* CURSOR_CLICKABLE_TEX;

	void onCreate() {
		CURSOR_TEX = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/cursor/cursor.png"));
		CURSOR_CLICKABLE_TEX = new Motor::Texture(Motor::ResourceLocation(resourcePackMod, "sprites/cursor/cursor_clickable.png"));
		CURSOR_TEX->load();
		CURSOR_CLICKABLE_TEX->load();
		addComponent<Motor::SpriteComponent>(CURSOR_TEX);
		getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
		getComponent<Motor::SpriteComponent>()->translatePosition_ = false;
		persistent_ = true;
		getriebe.getGame()->hideMouse();
		transform()->depth = 100;
	}

	void clickable(bool click) {
		if (click) {
			//getComponent<Motor::SpriteComponent>()->setTexture(CURSOR_CLICKABLE_TEX);
		}
		else {
			//getComponent<Motor::SpriteComponent>()->setTexture(CURSOR_TEX);
		}
	}

	void registerEvents() override {
		registerEvent(Motor::Events::mouseMotion.attach(&onMouse));
	}

	std::function<void(SDL_Event&)> onMouse = [this](SDL_Event& event) {
		transform()->position.set(event.button.x, event.button.y);
	};
};

extern CursorObject* CURSOR;