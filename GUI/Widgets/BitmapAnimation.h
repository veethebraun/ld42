//
// Created by vbrau on 8/12/2018.
//

#ifndef LD42_BITMAPANIMATION_H
#define LD42_BITMAPANIMATION_H


#include <vector>
#include "ImageWidget.h"

class BitmapAnimation : public ImageWidget {
public:
    BitmapAnimation(int x, int y, std::vector<ALLEGRO_BITMAP*>);
    void incrementFrame();
    void draw() override;

    ~BitmapAnimation() override = default;

private:
    std::vector<ALLEGRO_BITMAP*> frames;
    int frameNum;
public:
    virtual void setFrameNum(int frameNum);
};


#endif //LD42_BITMAPANIMATION_H
