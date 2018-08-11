//
// Created by vbrau on 4/18/2018.
//

#include <iostream>
#include "Game.h"
#include "GUI/Commands/TileClickCommand.h"
#include "GUI/Commands/TimeTickCommand.h"
#include "GUI/Commands/SelectBuildingCommand.h"

GameCommand * Game::handleCommand(GameCommand *cmd) {

    auto tile = dynamic_cast<TileClickCommand*>(cmd);
    if (tile != nullptr) {
        placeBuilding(tile->getI(), tile->getJ());
        std::cout << "[" << tile->getI() << ", " << tile->getJ() << "]" << std::endl;
    }

    auto build = dynamic_cast<SelectBuildingCommand*>(cmd);
    if (build != nullptr) {
        currentBuildingSelection = build->getBuildingType();
    }

    auto time = dynamic_cast<TimeTickCommand*>(cmd);
    if (time != nullptr) {
        handleTimeTick();
    }
    return nullptr;
}

void Game::init() {
    current_scene = SceneList::GAME;
    resource = new Resources();

    buildingsFree = true;
    currentBuildingSelection = BuildingType ::MAT_STORAGE;
    placeBuilding(0,0);
    buildingsFree = true;

    resource->resetResources();

    resource->addResources({0,0,30,0,0});
}

SceneList Game::getCurrentScene() const {
    return current_scene;
}

void Game::clearAfterFrame() {
}

void Game::placeBuilding(int x, int y) {
    if (currentBuildingSelection != BuildingType::NONE) {
        auto building = buildingFactory.getNewBuilding(currentBuildingSelection, x, y);
        if (building->canBuild(resource) || buildingsFree) {
            if (doesBuildingFit(building)) {
                Vector2d<int> bdgloc;
                bdgloc.x = x;
                bdgloc.y = y;
                buildingToGrid[building] = bdgloc;
                for (const auto &loc : building->getLocs()) {
                    int i = bdgloc.x + loc.x;
                    int j = bdgloc.y + loc.y;

                    buildings[i][j] = building;
                }
                building->onBuild(resource);
                currentBuildingSelection = BuildingType::NONE;
                setMessage("");
            } else {
                setMessage("bad location");
            }
        } else {
            setMessage("No Resources");
        }

    }
}

bool Game::hasBuilding(int x, int y) {
    return nullptr != buildings[x][y];
}

bool Game::doesBuildingFit(Building *building) {
    auto bdg_locs = building->getLocs();
    for (const auto &loc : bdg_locs) {
        int i = building->getX() + loc.x;
        int j = building->getY() + loc.y;

        if (!building->isLocRequired(loc))
            continue;

        if (i < 0 || i >= GRID_ROWS || j < 0 || j >= GRID_COLS)
            return false;
        if (hasBuilding(i, j))
            return false;
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
        item.first->resourceGeneration(resource);
    }

}

Resources *Game::getResource() const {
    return resource;
}

BuildingType Game::getCurrentBuildingSelection() const {
    return currentBuildingSelection;
}

const std::string &Game::getMessage() const {
    return message;
}

void Game::setMessage(const std::string &message) {
    Game::message = message;
}

