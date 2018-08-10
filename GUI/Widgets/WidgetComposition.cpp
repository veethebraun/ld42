//
// Created by vbrau on 4/22/2018.
//

#include "WidgetComposition.h"

void WidgetComposition::draw() {
    for (auto &&item : myWidgets) {
        item->draw();
    }
}

void WidgetComposition::addWidget(Widget *widget) {
    myWidgets.push_back(widget);
}

WidgetComposition::~WidgetComposition() {
    for (auto &&item : myWidgets) {
        delete item;
    }
}
