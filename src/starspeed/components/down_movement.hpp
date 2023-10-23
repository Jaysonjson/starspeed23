#pragma once
#include "motor/interfaces/component.hpp"
#include "motor/motor.hpp"

namespace StarSpeed {
    class DownMovementComponent : public Motor::IComponent {
    public:
        float speed_ = 0.2f;
        bool reset_ = false;
        float resetY_ = 0;
        void update() override {
            Motor::IComponent::update();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            //transform()->position.add({ 0, speed_ * delta });
            auto* owner = (Motor::GameObject*)getOwner();
            if(owner) {
                owner->transform()->position.add({ 0, speed_ * delta });
                if(reset_) {
                    if(owner->transform()->position.getY() >= resetY_) {
                        owner->transform()->position.setY(-1);
                    }
                }
            }

        }
    };
}