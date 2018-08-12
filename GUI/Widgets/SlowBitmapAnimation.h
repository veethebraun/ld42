#include <utility>

//
// Created by vbrau on 8/12/2018.
//

#ifndef LD42_SLOWBITMAPANIMATION_H
#define LD42_SLOWBITMAPANIMATION_H


#include "BitmapAnimation.h"

class SlowBitmapAnimation : public BitmapAnimation {
public:
    SlowBitmapAnimation(int x, int y, std::vector<ALLEGRO_BITMAP*>frames , int frameSkip) :
        BitmapAnimation(x, y, std::move(frames)), frameSkip(frameSkip) {};

    void setFrameNum(int frameNum) override;
private:
    int frameSkip;
};


#endif //LD42_SLOWBITMAPANIMATION_H
