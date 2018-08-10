//
// Created by vbrau on 4/15/2018.
//

#include <iostream>
#include "Button.h"
#include "Clickable.h"

bool Clickable::withinBox(int x, int y) {
    return ( x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

Clickable::Clickable(float x1, float x2, float y1, float y2) : x1(x1), x2(x2), y1(y1), y2(y2), command(nullptr) {}

void Clickable::setCommand(GameCommand *command) {
    Clickable::command = command;
}

GameCommand *Clickable::onClick() {
    return command;
}
