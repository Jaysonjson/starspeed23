# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.26
cmake_policy(SET CMP0009 NEW)

# LIBRARIES at CMakeLists.txt:42 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/libs/windows_release/*.a")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()

# LIBRARIES at CMakeLists.txt:42 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/libs/windows_release/*.dylib")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()

# LIBRARIES at CMakeLists.txt:42 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/libs/windows_release/*.lib")
set(OLD_GLOB
  "H:/starspeed23/libs/windows_release/FuchsLib.lib"
  "H:/starspeed23/libs/windows_release/Motor.lib"
  "H:/starspeed23/libs/windows_release/SDL3.lib"
  "H:/starspeed23/libs/windows_release/SDL3_image.lib"
  "H:/starspeed23/libs/windows_release/SDL3_mixer.lib"
  "H:/starspeed23/libs/windows_release/SDL3_ttf.lib"
  "H:/starspeed23/libs/windows_release/discord_game_sdk.dll.lib"
  "H:/starspeed23/libs/windows_release/libcrypto.lib"
  "H:/starspeed23/libs/windows_release/libcurl_a.lib"
  "H:/starspeed23/libs/windows_release/libssl.lib"
  "H:/starspeed23/libs/windows_release/zlib.lib"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()

# LIBRARIES at CMakeLists.txt:42 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/libs/windows_release/*.so")
set(OLD_GLOB
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()

# SOURCES_CPP at CMakeLists.txt:41 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/src/*.cpp")
set(OLD_GLOB
  "H:/starspeed23/src/achievements.cpp"
  "H:/starspeed23/src/discord.cpp"
  "H:/starspeed23/src/main.cpp"
  "H:/starspeed23/src/mine.cpp"
  "H:/starspeed23/src/objects.cpp"
  "H:/starspeed23/src/registries.cpp"
  "H:/starspeed23/src/resourcepack.cpp"
  "H:/starspeed23/src/sceneswitcher.cpp"
  "H:/starspeed23/src/splashs.cpp"
  "H:/starspeed23/src/textures.cpp"
  "H:/starspeed23/src/tinyfiledialogs.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()

# SOURCES_CPP at CMakeLists.txt:41 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "H:/starspeed23/src/*.hpp")
set(OLD_GLOB
  "H:/starspeed23/src/mine.hpp"
  "H:/starspeed23/src/starspeed/achievements.hpp"
  "H:/starspeed23/src/starspeed/components/down_movement.hpp"
  "H:/starspeed23/src/starspeed/cursor.hpp"
  "H:/starspeed23/src/starspeed/discord.hpp"
  "H:/starspeed23/src/starspeed/init/objects.hpp"
  "H:/starspeed23/src/starspeed/init/registries.hpp"
  "H:/starspeed23/src/starspeed/objects/background_spawner.json.hpp"
  "H:/starspeed23/src/starspeed/objects/bullets/bullet.hpp"
  "H:/starspeed23/src/starspeed/objects/enemy_spawner.hpp"
  "H:/starspeed23/src/starspeed/objects/explosion.hpp"
  "H:/starspeed23/src/starspeed/objects/music_handler.hpp"
  "H:/starspeed23/src/starspeed/objects/player_map.hpp"
  "H:/starspeed23/src/starspeed/objects/powerups/powerup.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/cent.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/cina.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/esent.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/faire.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/pine.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/saw.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/skrip.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemies/zenin.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/enemy.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/player.hpp"
  "H:/starspeed23/src/starspeed/objects/ships/ship.hpp"
  "H:/starspeed23/src/starspeed/objects/star.hpp"
  "H:/starspeed23/src/starspeed/objects/swdavatar.hpp"
  "H:/starspeed23/src/starspeed/planet.hpp"
  "H:/starspeed23/src/starspeed/planetutil.hpp"
  "H:/starspeed23/src/starspeed/profile.hpp"
  "H:/starspeed23/src/starspeed/resourcepack.hpp"
  "H:/starspeed23/src/starspeed/scenes/cell_map.hpp"
  "H:/starspeed23/src/starspeed/scenes/credits.hpp"
  "H:/starspeed23/src/starspeed/scenes/dm_titlescreen.hpp"
  "H:/starspeed23/src/starspeed/scenes/fight.hpp"
  "H:/starspeed23/src/starspeed/scenes/fight_end.hpp"
  "H:/starspeed23/src/starspeed/scenes/loading_scene.hpp"
  "H:/starspeed23/src/starspeed/scenes/login.hpp"
  "H:/starspeed23/src/starspeed/scenes/options.hpp"
  "H:/starspeed23/src/starspeed/scenes/splash.hpp"
  "H:/starspeed23/src/starspeed/scenes/titlescreen.hpp"
  "H:/starspeed23/src/starspeed/sceneswitcher.hpp"
  "H:/starspeed23/src/starspeed/splashs.hpp"
  "H:/starspeed23/src/starspeed/textures.hpp"
  "H:/starspeed23/src/starspeed/utility.hpp"
  "H:/starspeed23/src/tinyfiledialogs.hpp"
  "H:/starspeed23/src/zconf.hpp"
  "H:/starspeed23/src/zlib.hpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "H:/starspeed23/cmake-build-release/CMakeFiles/cmake.verify_globs")
endif()
