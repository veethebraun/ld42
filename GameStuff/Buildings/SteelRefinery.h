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
    std::string getBitmapName() override {
        return "steel_ref";
    };
    void onDestroy(Resources *resources) override;
    ~SteelRefinery() override = default;
    BuildingType getBuildingType() override { return BuildingType::STEEL; };
    std::valarray<int> getCost() override;
};


#endif //LD42_STEELREFINERY_H
