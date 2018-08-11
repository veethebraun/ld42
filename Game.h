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

#define GRID_ROWS 5
#define GRID_COLS 7


class Game {
public:
    GameCommand * handleCommand(GameCommand *cmd);

    void clearAfterFrame();
    SceneList getCurrentScene() const;

    void init();
    const std::map<Building *, Vector2d<int>> &getBuildingToGrid() const;

private:
    SceneList current_scene = SceneList::NONE;
    std::array<std::array<Building*,GRID_COLS>,GRID_ROWS> buildings = {{{nullptr}}};

    std::map<Building*,Vector2d<int>> buildingToGrid;

    void placeBuilding(int x, int y);
    bool hasBuilding(int x, int y);
    bool doesBuildingFit(Building* building);

    void printBuildings();

    void handleTimeTick();

    int resource = 0;
public:
    int getResource() const;
};


#endif //LD42_VBRAUN_GAME_H
