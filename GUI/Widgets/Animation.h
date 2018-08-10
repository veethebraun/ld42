//
// Created by vbrau on 4/23/2018.
//

#ifndef LD42_VBRAUN_DIFFERENTANIMATION_H
#define LD42_VBRAUN_DIFFERENTANIMATION_H


#include "WidgetComposition.h"

class Animation : public WidgetComposition {
public:

    Animation();

    void draw() override;

    void incrementFrame();
private:
    size_t frameNum;
};


#endif //LD42_VBRAUN_DIFFERENTANIMATION_H
