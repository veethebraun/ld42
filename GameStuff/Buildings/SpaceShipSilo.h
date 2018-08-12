//
// Created by vbrau on 8/12/2018.
//

#ifndef LD42_SPACESHIPSILO_H
#define LD42_SPACESHIPSILO_H


#include "../Building.h"

class SpaceShipSilo : public Building {
public:
    SpaceShipSilo(int x, int y);

    void resourceGeneration(Resources* resources) override {};
    std::string getBitmapName() override {
        return "rocket_silo";
    };
    void onDestroy(Resources *resources) override {};
    ~SpaceShipSilo() override = default;

protected:
    std::valarray<int> getCost() override;
};


#endif //LD42_SPACESHIPSILO_H
