#pragma once


#include <random>
#include "motor/object/gameobject.hpp"
#include "motor/sound/sound.hpp"
#include "motor/content/music.hpp"
#include "starspeed/profile.hpp"

namespace StarSpeed {
    class MusicHandler : public Motor::GameObject {
    public:
        std::thread* musicCheckThread;

        std::vector<Motor::Music*> MUSICS = {};

        Motor::Music* current = nullptr;
         
        void onCreate() override {
            setMusic();
            Motor::Music::changeChannelVolume(gameSettings->volume_);
            for (const auto &item: MUSICS) {
                item->file_->safeLoad();
            }
            musicCheckThread = new std::thread(&MusicHandler::checkMusic, this);
            musicCheckThread->detach();
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
            while (!awaitingDestroy_) {
                if (!Motor::Music::playing()) {
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
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            Mix_HaltMusic();
            for (const auto &item: MUSICS) {
                item->file_->unload();
            }
            delete musicCheckThread;
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