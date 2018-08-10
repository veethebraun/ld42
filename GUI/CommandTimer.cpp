//
// Created by vbrau on 8/4/2018.
//

#include "CommandTimer.h"

ALLEGRO_TIMER *CommandTimer::getTimer() const {
    return timer;
}

GameCommand *CommandTimer::getCmd() const {
    return cmd;
}

CommandTimer::CommandTimer(double time, GameCommand *cmd) : cmd(cmd) {
    timer = al_create_timer(time);
}

CommandTimer::~CommandTimer() {
    al_destroy_timer(timer);
    delete cmd;
}
