//
// Created by vbrau on 4/22/2018.
//

#ifndef LD42_VBRAUN_FILLEDRECTANGLE_H
#define LD42_VBRAUN_FILLEDRECTANGLE_H

#include "Widget.h"
#include "allegro5/allegro.h"

class FilledRectangle : public Widget {
public:
    FilledRectangle(float x1, float y1, float x2, float y2);
    FilledRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color);

    void draw() override;

    ~FilledRectangle() override;


private:
    float x1;
    float y1;
    float x2;
    float y2;

    ALLEGRO_BITMAP* bitmap;

    void createBitmap(float width, float height, ALLEGRO_COLOR color);
};


#endif //LD42_VBRAUN_FILLEDRECTANGLE_H
