#include "starspeed/sceneswitcher.hpp"
#include "starspeed/scenes/titlescreen.hpp"
#include "motor/motor.hpp"
namespace StarSpeed {
    void switchToTitleScreen() {
        getriebe.getGame()->switchScene(new TitleScreen());
    }
}