//
// Created by vbrau on 4/15/2018.
//

#include <iostream>
#include "Button.h"
#include "allegro5/allegro_primitives.h"
#include "../Commands/GameCommand.h"
#include "Widget.h"

GameCommand * Button::onClick() {
    //std::cout << "button was clicked" << std::endl;
    return Clickable::onClick();
}


Widget *Button::getWidget() const {
    return widget;
}

