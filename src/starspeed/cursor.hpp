#pragma once
#include "motor/object/gameobject.hpp"
#include "motor/components/sprite.hpp"
#include "starspeed/textures.hpp"


class CursorToolTipObject : public Motor::GameObject {
public:
	bool left = false;
	void onCreate() override {
		persistent_ = true;
		transform()->depth = 50;
		addComponent<Motor::SpriteComponent>(Motor::ResourceLocation(resourcePackMod, "fall.png"));
		getComponent<Motor::SpriteComponent>()->blendMode_ = SDL_BLENDMODE_BLEND;
		getComponent<Motor::SpriteComponent>()->translatePosition_ = false;
		getComponent<Motor::SpriteComponent>()->useCustomScale_ = true;
		getComponent<Motor::SpriteComponent>()->useCustomColor_ = true;
		getComponent<Motor::SpriteComponent>()->customColor_.set(0, 0, 0, 175);
		getComponent<Motor::SpriteComponent>()->customScale_.set(0, 0);

		addComponent<Motor::TextComponentBlended>(StarSpeed::Tex::GAME_FONT);
		getComponent<Motor::TextComponentBlended>()->translatePosition_ = false;
	}
	int toolTipX = 0;
	void setTooltip(const std::string& f) {
		//transform()->position.set(transform()->position.getX() + toolTipX, transform()->position.getY());
		if (getComponent<Motor::TextComponentBlended>()->getContent() != f) {
			int minX = 0;
            int maxX = 0;
            int maxY = 0;
			int advance = 0;
			for (int i = 0; i < f.size(); ++i) {
				if (i <= f.length()) {
					char c = f[i];
					int advanceStep = 0;
					TTF_GlyphMetrics(getComponent<Motor::TextComponentBlended>()->getFont()->get(), c, &minX, &maxX, NULL, &maxY, &advanceStep);
					advance += advanceStep;
				}
				else {
					break;
				}
			}
			toolTipX = ((minX + advance)) / 4  + 8;
			getComponent<Motor::TextComponentBlended>()->setContent(f);
            getComponent<Motor::TextComponentBlended>()->useCustomScale_ = true;
                getComponent<Motor::TextComponentBlended>()->customScale_.set((maxX * getriebe.getGame()->getRenderer()->widthDifference_) * 1.8, 45 * getriebe.getGame()->getRenderer()->heightDifference_);
                getComponent<Motor::SpriteComponent>()->customScale_.set( toolTipX * 4, 45 * getriebe.getGame()->getRenderer()->heightDifference_);
                transform()->scale.set(toolTipX * 4, 45 * getriebe.getGame()->getRenderer()->heightDifference_);
			//toolTipX *= getriebe.getGame()->getRenderer()->widthDifference_;
		}
	}

	void registerEvents() override {
		registerEvent(Motor::Events::mouseMotion.attach(&onMouse));
	}

	std::function<void(SDL_Event&)> onMouse = [this](SDL_Event& event) {
		if (event.button.x + toolTipX * getriebe.getGame()->getRenderer()->widthDifference_ * 4  > getriebe.getGame()->getWindow()->width_) {
			left = true;
		}
		else {
			left = false;
		}
		if (!left) {
			transform()->position.set(event.button.x + toolTipX * 2 * getriebe.getGame()->getRenderer()->widthDifference_, event.button.y);
		}
		else {
			transform()->position.set(event.button.x - toolTipX * 2 * getriebe.getGame()->getRenderer()->widthDifference_, event.button.y);
		}
        
	};

};

class CursorObject : public Motor::GameObject {
public:

	Motor::Texture* CURSOR_TEX;
	Motor::Texture* CURSOR_CLICKABLE_TEX;
	CursorToolTipObject* TOOLTIP = new CursorToolTipObject();
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

	int toolTipX;
	void setTooltip(const std::string& f) {
		TOOLTIP->setTooltip(f);
	}

	void resetTooltip() {
		TOOLTIP->getComponent<Motor::TextComponentBlended>()->setContent("");
		TOOLTIP->getComponent<Motor::SpriteComponent>()->customScale_.set(0, 0);
	}

	void clickable(bool click) {
		if (click) {
			getComponent<Motor::SpriteComponent>()->setTexture(CURSOR_CLICKABLE_TEX);
		}
		else {
			getComponent<Motor::SpriteComponent>()->setTexture(CURSOR_TEX);
		}
	}

    void update() override {
        Motor::GameObject::update();
        if(getriebe.getGame()->getWindow()->width_ > 1921) {
            getriebe.getGame()->changeResolution(1920, 1080);
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