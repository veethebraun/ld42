//
// Created by vbrau on 4/18/2018.
//

#ifndef LD42_VBRAUN_GAME_H
#define LD42_VBRAUN_GAME_H


#include <array>
#include "GUI/Commands/GameCommand.h"
#include "GUI/SceneList.h"

class Game {
public:
    GameCommand * handleCommand(GameCommand *cmd);

    void clearAfterFrame();
    SceneList getCurrentScene() const;

    void init();

private:
    SceneList current_scene = SceneList::NONE;
    int state = 0;
};


#endif //LD42_VBRAUN_GAME_H
