//
// Created by vbrau on 4/15/2018.
//

#ifndef LD42_VBRAUN_CLICKABLE_H
#define LD42_VBRAUN_CLICKABLE_H


#include "../Commands/GameCommand.h"

class Clickable {
private:
    GameCommand* command = nullptr;
protected:
    float x1{};
    float x2{};
    float y1{};
    float y2{};
public:
    virtual GameCommand * onClick();

    Clickable(float x1, float x2, float y1, float y2);

    Clickable() = default;

    bool withinBox(int x, int y);
    void setCommand(GameCommand *command);
};


#endif //LD42_VBRAUN_CLICKABLE_H
