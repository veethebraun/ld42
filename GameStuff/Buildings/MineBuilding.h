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
    std::string getBitmapName() override {
        return "mine";
    };
    void onDestroy(Resources *resources) override;
    ~MineBuilding() override = default;
    BuildingType getBuildingType() override { return BuildingType::MINE; };
    std::valarray<int> getCost() override;
};


#endif //LD42_MINEBUILDING_H
