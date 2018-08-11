#include <utility>

//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_BUILDING_H
#define LD42_BUILDING_H

#include <vector>
#include "Resources.h"
#include "../vectors.h"
#include <map>

class Building {
public:
    Building(int x, int y) : x(x), y(y) {};

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    virtual void resourceGeneration(Resources *resources) = 0;

    virtual void onBuild(Resources *resources);

    bool canBuild(Resources *resources);

    //virtual void onDestroy(Resources *resources) = 0;
    //virtual void onDelete(Resources *resources) = 0;
protected:
    virtual std::valarray<int> getCost() = 0;
    std::map<Vector2d<int>, bool> requiredLocs;

private:
    int x;
    int y;

    std::vector<Vector2d<int>> locs;
public:
    void setLocs(const std::vector<Vector2d<int>> &locs);

public:
    const std::vector<Vector2d<int>> &getLocs() const;
    bool isLocRequired(Vector2d<int> loc);
};


#endif //LD42_BUILDING_H
