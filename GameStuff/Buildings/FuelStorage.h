//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_FUELSTORAGE_H
#define LD42_FUELSTORAGE_H


#include "../Storage.h"

class FuelStorage : public Storage {
public:
    FuelStorage(int x, int y);

    void resourceGeneration(Resources* resources) override {};
    std::string getBitmapName() override {
        return "fuel_store";
    };
    ~FuelStorage() override = default;
    BuildingType getBuildingType() override { return BuildingType::FUEL_STORAGE; };
    std::valarray<int> getCost() override;
protected:
    std::valarray<int> getStorage() override;

};


#endif //LD42_FUELSTORAGE_H
