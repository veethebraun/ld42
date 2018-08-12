#include <utility>
#include <iostream>

//
// Created by vbrau on 8/12/2018.
//

#include "BitmapAnimation.h"

BitmapAnimation::BitmapAnimation(int x, int y, std::vector<ALLEGRO_BITMAP *> bitmaps) :
    ImageWidget(x, y, nullptr) {

    frames = std::move(bitmaps);
    setBitmap(frames.front());
    frameNum = 0;
}

void BitmapAnimation::incrementFrame() {
    frameNum++;

    if (frameNum >= frames.size()) {
        frameNum = 0;
    }
}

void BitmapAnimation::draw() {
    al_draw_bitmap(frames.at(static_cast<unsigned int>(frameNum)), (float) x, (float) y, 0);
}

void BitmapAnimation::setFrameNum(int frameNum) {
    BitmapAnimation::frameNum = static_cast<int>(frameNum % frames.size());
}


