//
// Created by vbrau on 4/22/2018.
//

#ifndef LD42_VBRAUN_IMAGEWIDGET_H
#define LD42_VBRAUN_IMAGEWIDGET_H


#include <string>
#include "Widget.h"
#include "allegro5/allegro.h"

class ImageWidget : public Widget {
public:
    ImageWidget(int x, int y, ALLEGRO_BITMAP* bitmap);

    void draw() override;
private:
    int x;
    int y;
    ALLEGRO_BITMAP* bitmap;
};


#endif //LD42_VBRAUN_IMAGEWIDGET_H
