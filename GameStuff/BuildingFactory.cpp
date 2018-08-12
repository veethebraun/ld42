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

std::vector<std::string> BuildingFactory::getFrameNames(BuildingType buildingType) {
    std::vector<std::string> frames;

    switch (buildingType) {
        case BuildingType::MINE:
            frames.emplace_back("mine");
            break;

        case BuildingType::WIND:
            frames.emplace_back("wind_power_f1");
            frames.emplace_back("wind_power_f2");
            frames.emplace_back("wind_power_f3");
            frames.emplace_back("wind_power_f4");
            frames.emplace_back("wind_power_f5");
            break;

        case BuildingType::STEEL:
            frames.emplace_back("steel_ref");
            break;

        case BuildingType::MAT_STORAGE:
            frames.emplace_back("mat_store");
            break;

        case BuildingType::FUEL:
            frames.emplace_back("fuel_ref");
            break;

        case BuildingType::FUEL_STORAGE:
            frames.emplace_back("fuel_store");
            break;

        case BuildingType::ROCKET:
            frames.emplace_back("rocket_silo");
            break;

        case BuildingType::NONE:
            break;
    }
    return frames;
}

std::valarray<int> BuildingFactory::getCosts(BuildingType buildingType) {
    switch (buildingType) {
        case BuildingType::MINE:
            return {MINE_POWER,0,MINE_STEEL_COST,0,0};

        case BuildingType::WIND:
            return {0, 0, WIND_STEEL_COST, 0, 0};

        case BuildingType::STEEL:
            return {STEEL_REFINERY_POWER,0,STEEL_REFINERY_STEEL_COST,0,0};

        case BuildingType::MAT_STORAGE:
            return {0,0,MIN_STORE_STEEL_COST,0,0};

        case BuildingType::FUEL:
            return {FUEL_REFINERY_POWER, 0, FUEL_REFINERY_STEEL_COST, 0, 0};

        case BuildingType::FUEL_STORAGE:
            return {FUEL_STORE_POWER, 0, FUEL_STORE_STEEL_COST, 0, 0};

        case BuildingType ::ROCKET:
            return {0, 0, ROCKET_STEEL_COST, ROCKET_FUEL_COST, 0};

        case BuildingType::NONE:
            return {0,0,0,0,0};
    }
}

std::string BuildingFactory::getProvides(BuildingType buildingType) {
    switch (buildingType) {
        case BuildingType::MINE:
            return "Mines " + std::to_string(MINE_RATE) + " / s Raw Materials";

        case BuildingType::WIND:
            return "Generates " + std::to_string(WIND_POWER_GEN) + " Power";

        case BuildingType::STEEL:
            return "Turns " + std::to_string(STEEL_RATE) + " Raw Materials to " + std::to_string(STEEL_RATE) + " Steel /s";

        case BuildingType::MAT_STORAGE:
            return "Stores " + std::to_string(MIN_STORE_AMOUNT) + " Storage for Steel and Raw Materials";

        case BuildingType::FUEL:
            return "Turns " + std::to_string(FUEL_REFINERY_RATE) + " Raw Materials to " + std::to_string(FUEL_REFINERY_RATE) + " Fuel /s";

        case BuildingType::FUEL_STORAGE:
            return "Stores " + std::to_string(FUEL_STORE_AMOUNT) + " Fuel";

        case BuildingType ::ROCKET:
            return "Launch to ESCAPE!";

        case BuildingType::NONE:
            return "";
    }
}

std::string getBuildingTypeStr(BuildingType buildingType) {
    switch (buildingType) {
        case BuildingType::MINE:
            return "Mine";

        case BuildingType::WIND:
            return "Wind Farm";

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
            return "None selected..";
    }
}
