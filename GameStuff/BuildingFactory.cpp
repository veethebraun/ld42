//
// Created by vbrau on 8/11/2018.
//

#include "BuildingFactory.h"
#include "Buildings/WindBuilding.h"
#include "Buildings/MineBuilding.h"
#include "Buildings/SteelRefinery.h"
#include "Buildings/MaterialStorage.h"
#include "Buildings/FuelRefinery.h"
#include "Buildings/FuelStorage.h"
#include "Buildings/SpaceShipSilo.h"

Building *BuildingFactory::getNewBuilding(BuildingType buildingType, int x, int y) {
    switch (buildingType) {
        case BuildingType::MINE:
            return getBuilding<MineBuilding>(x, y);
        case BuildingType ::WIND:
            return getBuilding<WindBuilding>(x, y);
        case BuildingType ::STEEL:
            return getBuilding<SteelRefinery>(x, y);
        case BuildingType ::MAT_STORAGE:
            return getBuilding<MaterialStorage>(x, y);
        case BuildingType ::FUEL:
            return getBuilding<FuelRefinery>(x,y);
        case BuildingType ::FUEL_STORAGE:
            return getBuilding<FuelStorage>(x, y);
        case BuildingType ::ROCKET:
            return getBuilding<SpaceShipSilo>(x, y);
        case BuildingType::NONE: return nullptr;
    }
}

template<typename T>
T *BuildingFactory::getBuilding(int x, int y) {
    return new T(x, y);
}

std::string getBuildingTypeStr(BuildingType buildingType) {
    switch (buildingType) {
        case BuildingType::MINE:
            return "Mine";

        case BuildingType::WIND:
            return "Wind";

        case BuildingType::STEEL:
            return "Steel Refinery";

        case BuildingType::MAT_STORAGE:
            return "Material Storage";

        case BuildingType::FUEL:
            return "Fuel Refinery";

        case BuildingType::FUEL_STORAGE:
            return "Fuel Storage";
        case BuildingType ::ROCKET:
            return "Rocket Silo";

        case BuildingType::NONE:
            return "NONE";
    }
}
