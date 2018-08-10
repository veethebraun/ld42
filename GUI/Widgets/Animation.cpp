//
// Created by vbrau on 4/23/2018.
//

#include "Animation.h"

void Animation::draw() {
    myWidgets.at(frameNum)->draw();
}

void Animation::incrementFrame() {
    frameNum++;
    if (frameNum >= myWidgets.size()) {
        frameNum = 0;
    }
}

Animation::Animation() : frameNum(0) {}
