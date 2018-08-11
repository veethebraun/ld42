//
// Created by vbrau on 4/18/2018.
//

#ifndef LD42_VBRAUN_GAME_H
#define LD42_VBRAUN_GAME_H


#include <array>
#include <map>
#include "GUI/Commands/GameCommand.h"
#include "GUI/SceneList.h"
#include "GameStuff/Building.h"
#include "vectors.h"
#include "GameStuff/Resources.h"
#include "GameStuff/BuildingFactory.h"
#include "defs.h"

#define NUM_TIME_STEPS_FOR_DROP 6

class Game {
public:
    GameCommand * handleCommand(GameCommand *cmd);

    void clearAfterFrame();
    SceneList getCurrentScene() const;

    void init();

    Resources *getResource() const;
    const char * getMessage() const;

    void setMessage(const char *message);

    BuildingType getCurrentBuildingSelection() const;

private:
    SceneList current_scene = SceneList::NONE;
    std::array<std::array<bool,GRID_COLS>,GRID_ROWS> buildings = {{{false}}};

    std::vector<Building*> activeBuildings;
public:
    const std::vector<Building *> &getActiveBuildings() const;

private:

    void placeBuilding(int x, int y);
    bool hasBuilding(int x, int y);
    bool doesBuildingFit(Building* building);

    void printBuildings();

    void handleTimeTick();

    Resources* resource = nullptr;

    BuildingFactory buildingFactory;

    BuildingType currentBuildingSelection = BuildingType::NONE;

    const char* message = "";

    bool buildingsFree = false;

    void dropBuildings();

    void populateBuilding(Building *building);

    int dropCounter = 0;

    void fillBuildings();
};


#endif //LD42_VBRAUN_GAME_H
