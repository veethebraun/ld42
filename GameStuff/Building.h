#include <utility>

//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_BUILDING_H
#define LD42_BUILDING_H

#include <vector>
#include "Resources.h"
#include "../vectors.h"
#include "../defs.h"
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


    bool isLocRequired(Point2d loc);

    virtual std::string getBitmapName() = 0;

    void dropLevel(Resources *resources);
    virtual void onDestroy(Resources *resources) = 0;

    Point2d getXY();

    bool isOnBoard(int max_x, int max_y);

    virtual ~Building() = default;

protected:
    virtual std::valarray<int> getCost() = 0;

    std::vector<Point2d> requiredLocs;

    bool destroyed = false;
public:
    bool isDestroyed() const;

protected:
    std::vector<Point2d> locs;
public:
    const std::vector<Point2d> &getLocs() const;

private:
    int x;
    int y;


};


#endif //LD42_BUILDING_H
