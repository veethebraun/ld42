//
// Created by vbrau on 4/22/2018.
//

#include "FilledRectangle.h"
#include "allegro5/allegro_primitives.h"

FilledRectangle::FilledRectangle(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2)  {
    auto color = al_map_rgba(0,0,0,0);
    createBitmap(x2-x1, y2-y1, color);
}

FilledRectangle::FilledRectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color) : x1(x1), y1(y1), x2(x2), y2(y2)  {
    createBitmap(x2-x1, y2-y1, color);
}

void FilledRectangle::draw() {
    al_draw_bitmap(bitmap, x1, y1, 0);
}

void FilledRectangle::createBitmap(float width, float height, ALLEGRO_COLOR color) {
    bitmap = al_create_bitmap( (int)width, (int)height );
    al_set_target_bitmap(bitmap);
    al_draw_filled_rectangle(0, 0, width, height, color);

}

FilledRectangle::~FilledRectangle() {
    al_destroy_bitmap(bitmap);
}
