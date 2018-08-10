//
// Created by vbrau on 4/22/2018.
//

#ifndef LD42_VBRAUN_WIDGETCOMPOSITION_H
#define LD42_VBRAUN_WIDGETCOMPOSITION_H


#include "Widget.h"
#include <vector>

class WidgetComposition : public Widget {

protected:
    std::vector<Widget*> myWidgets;
public:
    void draw() override;

    void addWidget(Widget *widget);

    ~WidgetComposition() override;

};


#endif //LD42_VBRAUN_WIDGETCOMPOSITION_H
