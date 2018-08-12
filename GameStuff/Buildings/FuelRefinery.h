//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_FUELREFINERY_H
#define LD42_FUELREFINERY_H


#include "../Building.h"

class FuelRefinery : public Building {
public:
    FuelRefinery(int x, int y);

    void resourceGeneration(Resources* resources) override;
    void onDestroy(Resources *resources) override;

    std::string getBitmapName() override {
        return "fuel_ref";
    };

    ~FuelRefinery() override = default;
    BuildingType getBuildingType() override { return BuildingType::FUEL; };
    std::valarray<int> getCost() override;

};


#endif //LD42_FUELREFINERY_H
