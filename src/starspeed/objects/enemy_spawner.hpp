#pragma once
#include "ships/enemy.hpp"
#include "ships/player.hpp"
#include "ships/enemies/saw.hpp"
#include "ships/enemies/cent.hpp"
#include "ships/enemies/zenin.hpp"
#include "ships/enemies/cina.hpp"
#include "ships/enemies/esent.hpp"
#include "ships/enemies/faire.hpp"
#include "ships/enemies/skrip.hpp"
#include "ships/enemies/pine.hpp"
#include "star.hpp"
#include "starspeed/components/down_movement.hpp"
#include <random>

namespace StarSpeed {
    class EnemySpawner : public Motor::GameObject {
    public:
        PlayerShip* PLAYER = nullptr;

        std::vector<std::pair<EnemyShip, double>> SPAWNS{
            {SawEnemy{}, 0.9}
        };
        

        float spawnCounter = 0;
        float starCounter = 0;
        int* progress;
        void fixedUpdate() override {
            Motor::GameObject::fixedUpdate();
            float delta = getriebe.getGame()->getDelta().deltaTime;
            spawnCounter += 0.1f * delta;
            starCounter += 0.1f * delta;

            if (8 < starCounter) {
                starCounter = 0;
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<double> dist2(32, 1400);
                std::uniform_real_distribution<double> dist3(900, 1200);
                Star* STAR = new Star();
                STAR->addComponent<DownMovementComponent>();
                STAR->transform()->position.set(dist2(mt), PLAYER->transform()->position.getY() - dist3(mt));
                STAR->addToCurrentScene(false);
            }

            if(70 < spawnCounter && *progress < 96) {
                spawnCounter = 0;
                std::random_device rd;
                std::mt19937 mt(rd());
                std::uniform_real_distribution<double> dist(0, 1);
                std::uniform_real_distribution<double> dist2(32, 1400);
                std::uniform_real_distribution<double> dist3(800, 1200);
                /*for (std::pair<EnemyShip, double>& spawnPair : SPAWNS) {
                    if (dist(mt) < spawnPair.second) {
                        SawEnemy* ENEMY_SHIP = new SawEnemy();
                        ENEMY_SHIP->transform()->position.set(1920 / 3, PLAYER->transform()->position.getY() - 800);
                        ENEMY_SHIP->addToCurrentScene();
                        EnemyShip* ENEMY_SHIP = spawnPair.first.clone();
                        ENEMY_SHIP->transform()->position.set(1920 / 3, PLAYER->transform()->position.getY() - 800);
                        ENEMY_SHIP->addToCurrentScene();
                    }
                }*/
                float rnd = dist(mt);
                if (rnd < 0.075) {
                    SawEnemy* ENEMY_SHIP = new SawEnemy();
                    ENEMY_SHIP->transform()->position.set(dist2(mt), PLAYER->transform()->position.getY() - dist3(mt));
                    ENEMY_SHIP->addToCurrentScene(false);
                }

                if (rnd < 0.05) {
                    CentEnemy* ENEMY_SHIP = new CentEnemy();
                    ENEMY_SHIP->transform()->position.set(dist2(mt), PLAYER->transform()->position.getY() - dist3(mt));
                    ENEMY_SHIP->addToCurrentScene(false);
                }

                if (rnd < 0.2) {
                    CinaEnemy* ENEMY_SHIP = new CinaEnemy();
                    ENEMY_SHIP->transform()->position.set(dist2(mt), PLAYER->transform()->position.getY() - dist3(mt));
                    ENEMY_SHIP->addToCurrentScene(false);
                }

                if (rnd < 0.6) {
                    ZeninEnemy* ENEMY_SHIP = new ZeninEnemy();
                    ENEMY_SHIP->transform()->position.set(dist2(mt), PLAYER->transform()->position.getY() - dist3(mt));
                    ENEMY_SHIP->addToCurrentScene(false);
                }
            }
        }
    };
}