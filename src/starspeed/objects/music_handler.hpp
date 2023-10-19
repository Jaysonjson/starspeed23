#pragma once


#include <random>
#include "motor/object/gameobject.hpp"
#include "motor/sound/sound.hpp"
#include "motor/content/music.hpp"

namespace StarSpeed {
    class MusicHandler : public Motor::GameObject {
    public:

        std::vector<Motor::Music*> MUSICS = {
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/its_space.mp3"))),
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/space_echoes.mp3"))),
                new Motor::Music(new Motor::MusicFile(Motor::ResourceLocation(fallbackMod, "audio/music/amythical/starspeed.mp3")))

        };

        void onCreate() override {

            for (const auto &item: MUSICS) {
                item->file_->safeLoad();
            }

        }

        void fixedUpdate() override {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0, MUSICS.size());
            if(!Mix_PlayingMusic()) {
                MUSICS[dist(mt)]->playFade(500);
            }
        }
    };
}