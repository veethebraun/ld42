//
// Created by vbrau on 4/22/2018.
//

#include <iostream>
#include "ImageWidget.h"

ImageWidget::ImageWidget(int x, int y, ALLEGRO_BITMAP* bitmap) : x(x), y(y), bitmap(bitmap) {
}

void ImageWidget::draw() {
    al_draw_bitmap(bitmap, (float) x, (float) y, 0);
}

void ImageWidget::setBitmap(ALLEGRO_BITMAP *bitmap) {
    ImageWidget::bitmap = bitmap;
}
