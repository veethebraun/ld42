//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_STORAGE_H
#define LD42_STORAGE_H


#include "Building.h"

class Storage : public Building {
public:
    Storage(int x, int y) : Building(x, y) {};
    void onBuild(Resources* resources) override;
    void onDestroy(Resources *resources) override;

protected:
    virtual std::valarray<int> getStorage() = 0;
};


#endif //LD42_STORAGE_H
