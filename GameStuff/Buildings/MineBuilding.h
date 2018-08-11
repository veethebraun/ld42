//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_MINEBUILDING_H
#define LD42_MINEBUILDING_H


#include "../Building.h"

class MineBuilding : public Building {
public:
    MineBuilding(int x, int y);

    void resourceGeneration(Resources* resources) override;
protected:
    std::valarray<int> getCost() override;
};


#endif //LD42_MINEBUILDING_H
