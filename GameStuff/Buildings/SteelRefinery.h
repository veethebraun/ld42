//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_STEELREFINERY_H
#define LD42_STEELREFINERY_H


#include "../Building.h"

class SteelRefinery : public Building {
public:
    SteelRefinery(int x, int y);

    void resourceGeneration(Resources* resources) override;
protected:
    std::valarray<int> getCost() override;
};


#endif //LD42_STEELREFINERY_H
