#pragma once


#include <random>
#include "motor/object/gameobject.hpp"
#include "motor/sound/sound.hpp"
#include "motor/content/music.hpp"
#include "starspeed/profile.hpp"

namespace StarSpeed {

    constexpr std::string AMYTHICAL = "Amythical";

    struct MusicEntry {
        Motor::Music* music_ = nullptr;
        std::string author_ = "";
        std::string title_ = "";
    };

    class MusicHandler : public Motor::GameObject {
    public:
        std::thread* musicCheckThread;

        std::vector<Motor::Music*> MUSICS = {};

        Motor::Music* current = nullptr;
        bool stop_ = false;
        bool running_ = true;
        void onCreate() override {
            setMusic();
            Motor::Music::changeChannelVolume(gameSettings->volume_);
            for (const auto &item: MUSICS) {
                item->file_->safeLoad();
            }
            musicCheckThread = new std::thread(&MusicHandler::checkMusic, this);
            musicCheckThread->detach();
            persistent_ = true;
        }

        virtual void setMusic() {
            MUSICS = {
                    new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/its_space.mp3"))),
                    new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/space_echoes.mp3"))),
                    new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/starspeed.mp3")))
            };
        }


        void checkMusic() {
           // for (const auto& item : MUSICS) {
                //item->file_->safeLoad();
           // }
            while (running_) {
                if (!Motor::Music::playing() && !stop_) {
                    std::random_device rd;
                    std::mt19937 mt(rd());
                    std::uniform_real_distribution<double> dist(0, MUSICS.size());
                    current = MUSICS[dist(mt)];
                    current->playFade(4500);
                }
                if (current) {
                    if (current->duration() - 5 < current->position()) {
                        Motor::Music::fadeOut(4500);
                    }
                }
                if(stop_) {
                    Mix_HaltMusic();
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            Mix_HaltMusic();
            for (const auto &item: MUSICS) {
                item->file_->unload();
            }
            delete musicCheckThread;
        }

        void onSceneSwitch(Motor::Scene *currentScene, Motor::Scene *newScene, bool &shouldDelete) override {
            stop_ = true;
        }
    };

    class DMTSMusicHandler : public MusicHandler {
    public:

        void setMusic() override {
            MUSICS = {
                    new Motor::Music(new Motor::MusicFile(
                            Motor::ResourceLocation(fallbackMod, "audio/music/amythical/dm/i_am_the_surgeon.mp3"))),
                    new Motor::Music(new Motor::MusicFile(
                            Motor::ResourceLocation(fallbackMod, "audio/music/amythical/dm/professor_whomstdve.mp3"))),
                    new Motor::Music(new Motor::MusicFile(
                            Motor::ResourceLocation(fallbackMod, "audio/music/amythical/dm/each_of_the_peculiar_organisms.mp3")))
            };
        }
    };
}