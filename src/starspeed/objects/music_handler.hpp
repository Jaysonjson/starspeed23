#pragma once


#include <random>
#include "motor/object/gameobject.hpp"
#include "motor/sound/sound.hpp"
#include "motor/content/music.hpp"

namespace StarSpeed {
    class MusicHandler : public Motor::GameObject {
    public:
        std::thread* musicCheckThread;

        std::vector<Motor::Music*> MUSICS = {
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/its_space.mp3"))),
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/space_echoes.mp3"))),
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/starspeed.mp3")))

        };

        Motor::Music* current = nullptr;

        void onCreate() override {
            Motor::Music::changeChannelVolume(1);
            for (const auto &item: MUSICS) {
                item->file_->safeLoad();
            }
            musicCheckThread = new std::thread(&MusicHandler::checkMusic, this);
            musicCheckThread->detach();
        }


        void checkMusic() {
           // for (const auto& item : MUSICS) {
                //item->file_->safeLoad();
           // }
            while (true) {
                if (!Mix_PlayingMusic()) {
                    std::random_device rd;
                    std::mt19937 mt(rd());
                    std::uniform_real_distribution<double> dist(0, MUSICS.size());
                    current = MUSICS[dist(mt)];
                    current->playFade(4500);
                    //Mix_FadeOutMusic(1500);
                }
                if (current) {
                    if (current->duration() - 5 < current->position()) {
                        Mix_FadeOutMusic(4500);
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    };
}