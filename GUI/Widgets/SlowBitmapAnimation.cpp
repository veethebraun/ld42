//
// Created by vbrau on 8/12/2018.
//

#include <iostream>
#include "SlowBitmapAnimation.h"

void SlowBitmapAnimation::setFrameNum(int frameNum) {
    BitmapAnimation::setFrameNum(frameNum / frameSkip);
}
