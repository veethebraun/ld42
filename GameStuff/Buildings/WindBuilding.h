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
    std::string getBitmapName() override {
        return "wind_power";
    };
    void onDestroy(Resources *resources) override;
    ~WindBuilding() override = default;
protected:
    std::valarray<int> getCost() override;

};


#endif //LD42_WINDBUILDING_H
