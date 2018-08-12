//
// Created by vbrau on 8/11/2018.
//

#ifndef LD42_BUILDINGFACTORY_H
#define LD42_BUILDINGFACTORY_H

#include "Building.h"
#include <string>
#include "BuildingList.h"


std::string getBuildingTypeStr(BuildingType buildingType);

class BuildingFactory {
public:

    Building* getNewBuilding(BuildingType buildingType, int x, int y);

    static std::vector<std::string> getFrameNames(BuildingType buildingType);
    static std::valarray<int> getCosts(BuildingType buildingType);
    static std::string getProvides(BuildingType buildingType);
    static int getAnimSpeed(BuildingType buildingType);
private:
    template<typename T>
    T* getBuilding(int x, int y);


};


#endif //LD42_BUILDINGFACTORY_H
