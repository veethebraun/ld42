//
// Created by vbrau on 4/18/2018.
//

#include <iostream>
#include "Game.h"
#include "GUI/Commands/TileClickCommand.h"
#include "GUI/Commands/TimeTickCommand.h"

GameCommand * Game::handleCommand(GameCommand *cmd) {

    auto tile = dynamic_cast<TileClickCommand*>(cmd);
    if (tile != nullptr) {
        placeBuilding(tile->getI(), tile->getJ());
        std::cout << "[" << tile->getI() << ", " << tile->getJ() << "]" << std::endl;
    }

    auto time = dynamic_cast<TimeTickCommand*>(cmd);
    if (time != nullptr) {
        handleTimeTick();
    }
    return nullptr;
}

void Game::init() {
    current_scene = SceneList::GAME;
    placeBuilding(0, 0);
}

SceneList Game::getCurrentScene() const {
    return current_scene;
}

void Game::clearAfterFrame() {
}

void Game::placeBuilding(int x, int y) {
    auto building = new Building(x, y, 3, 2);
    if (doesBuildingFit(building)) {
        Vector2d<int> loc;
        loc.x = x;
        loc.y = y;
        buildingToGrid[building] = loc;
        for (int i=building->getX(); i<building->getX() + building->getX_size(); i++) {
            for (int j = building->getY(); j < building->getY() + building->getY_size(); j++) {
                buildings[i][j] = building;
            }
        }
    }
    printBuildings();
}

bool Game::hasBuilding(int x, int y) {
    return nullptr != buildings[x][y];
}

bool Game::doesBuildingFit(Building *building) {
    for (int i=building->getX(); i<building->getX() + building->getX_size(); i++)
    {
        for (int j=building->getY(); j<building->getY() + building->getY_size(); j++)
        {
            if (i < 0 || i >= GRID_ROWS || j < 0 || j >= GRID_COLS)
                return false;
            if (hasBuilding(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

const std::map<Building *, Vector2d<int>> &Game::getBuildingToGrid() const {
    return buildingToGrid;
}

void Game::printBuildings() {
    for (int i=0; i<GRID_ROWS; i++){
        for (int j=0; j<GRID_COLS; j++) {
            std::cout << (nullptr != buildings[i][j]);
        }
        std::cout << std::endl;
    }

}

void Game::handleTimeTick() {
    for (const auto &item : buildingToGrid) {
        resource += item.first->output_resources();
    }

}

int Game::getResource() const {
    return resource;
}

