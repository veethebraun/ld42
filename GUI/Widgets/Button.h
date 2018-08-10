//
// Created by vbrau on 4/15/2018.
//

#ifndef LD42_VBRAUN_BUTTON_H
#define LD42_VBRAUN_BUTTON_H


#include "Clickable.h"
#include "../Commands/GameCommand.h"
#include "Widget.h"


class Button : public Clickable {

public:
    Button(float x1, float x2, float y1, float y2, Widget *widget) :
            Clickable(x1, x2, y1, y2),
            widget(widget) {}

    Button(float x1, float x2, float y1, float y2) :
            Clickable(x1, x2, y1, y2),
            widget(nullptr) {}

    GameCommand * onClick() override;

    Widget *getWidget() const;

private:
    Widget* widget;
};


#endif //LD42_VBRAUN_BUTTON_H
