//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_WINDBUILDING_H
#define LD42_WINDBUILDING_H


#include "../Building.h"

class WindBuilding : public Building {
public:
    WindBuilding(int x, int y);

    void resourceGeneration(Resources* resources) override {};
protected:
    std::valarray<int> getCost() override;

};


#endif //LD42_WINDBUILDING_H
