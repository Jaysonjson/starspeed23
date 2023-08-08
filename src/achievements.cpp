#include "starspeed/achievements.hpp"
#include "motor/log.hpp"
#include "starspeed/profile.hpp"

namespace StarSpeed {
    std::vector<Achievement*> achievements{};

    void unlockAchievement(std::string id) {
        for(Achievement* achievement : achievements) {
            if(achievement->isUnlocked()) continue;
            if(achievement->getID() == id) {
                achievement->setUnlocked(true);
                ACHIEVEMENT_UNLOCK_HEADER->trigger = true;
                ACHIEVEMENT_UNLOCK_HEADER->description_ = achievement->getDescription();
                playerProfile->getAchievements().push_back(achievement->getID());
                MOTOR_LOG("Unlocked Achievement: " + id);
                return;
            }
        }
    }

    void unlockAchievement(Achievement* achievement) {
        unlockAchievement(achievement->getID());
    }

    void addAchievements() {
        achievements.emplace_back(Achmts::START_GAME);
        achievements.emplace_back(Achmts::LOGIN_SWD);
        achievements.emplace_back(Achmts::DIE);
        achievements.emplace_back(Achmts::KILL_ENEMY);
        achievements.emplace_back(Achmts::WIN_ROUND);

        for (std::string& str : playerProfile->getAchievements()) {
            MOTOR_LOG(str)
            for (Achievement* achievement : achievements) {
                if (achievement->getID() == str) {
                    achievement->setUnlocked(true);
                    return;
                }
            }
        }
    }


    namespace Achmts {
        Achievement* START_GAME = new Achievement("start_game", "You started the Game!");
        Achievement* LOGIN_SWD = new Achievement("login_swd", "You logged into your SWD Account!");
        Achievement* DIE = new Achievement("die_fight", "You died in a Fight!");
        Achievement* KILL_ENEMY = new Achievement("kill_enemy", "You killed a Enemy!");
        Achievement* WIN_ROUND = new Achievement("win_round", "You won a Round!");
    }
    AchievementUnlockHeader* ACHIEVEMENT_UNLOCK_HEADER = new AchievementUnlockHeader();
}