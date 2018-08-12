//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_MATERIALSTORAGE_H
#define LD42_MATERIALSTORAGE_H


#include "../Storage.h"

class MaterialStorage : public Storage {
public:
    MaterialStorage(int x, int y);

    void resourceGeneration(Resources* resources) override {};
    std::string getBitmapName() override {
        return "mat_store";
    };

    ~MaterialStorage() override = default;
    BuildingType getBuildingType() override { return BuildingType::MAT_STORAGE; };
    std::valarray<int> getCost() override;
protected:
    std::valarray<int> getStorage() override;

};


#endif //LD42_MATERIALSTORAGE_H
