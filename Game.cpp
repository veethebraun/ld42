//
// Created by vbrau on 4/18/2018.
//

#include <iostream>
#include "Game.h"
#include "GUI/Commands/TileClickCommand.h"
#include "GUI/Commands/TimeTickCommand.h"
#include "GUI/Commands/SelectBuildingCommand.h"

GameCommand * Game::handleCommand(GameCommand *cmd) {

    std::cout << "have " << activeBuildings.size() << " buildings.." << std::endl;
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
    fillBuildings();
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
        std::cout << "placing: " << building << " at " << building->getX() << std::endl;
        if (building->canBuild(resource) || buildingsFree) {
            if (doesBuildingFit(building)) {
                populateBuilding(building);
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
    return buildings.at((size_t) x).at((size_t )y);
}

bool Game::doesBuildingFit(Building *building) {
    auto bdg_locs = building->getLocs();
    for (const auto &loc : bdg_locs) {
        int i = building->getX() + loc[0];
        int j = building->getY() + loc[1];

        if (!building->isLocRequired(loc))
            continue;

        if (i < 0 || i >= GRID_ROWS || j < 0 || j >= GRID_COLS)
            return false;
        if (hasBuilding(i, j))
            return false;
    }
    return true;
}

void Game::printBuildings() {
    for (size_t i=0; i<GRID_ROWS; i++){
        for (size_t j=0; j<GRID_COLS; j++) {
            std::cout << (buildings.at(i).at(j));
        }
        std::cout << std::endl;
    }

}

void Game::handleTimeTick() {
    for (const auto &building : activeBuildings) {
        building->resourceGeneration(resource);
    }

    dropCounter++;
    if (dropCounter > NUM_TIME_STEPS_FOR_DROP)
    {
        dropBuildings();
        dropCounter = 0;
    }
}

Resources *Game::getResource() const {
    return resource;
}

BuildingType Game::getCurrentBuildingSelection() const {
    return currentBuildingSelection;
}

const char * Game::getMessage() const {
    return message;
}

void Game::setMessage(const char *message) {
    Game::message = message;
}

void Game::dropBuildings() {
    fillBuildings();
    std::cout << "dropBuildings" << std::endl;

    std::vector<Building*> buildingsToRemove;
    for (const auto &building : activeBuildings) {
        std::cout << "  checking: " << building << std::endl;
        building->dropLevel(resource);
        std::cout << "  now at: " << building->getXY()[0] << std::endl;
        if (!building->isOnBoard(GRID_ROWS, GRID_COLS))
        {
            std::cout << "  NO LONGER ON BOARD" << std::endl;
           buildingsToRemove.push_back(building) ;
        }
    }

    activeBuildings.erase( remove_if( begin(activeBuildings),end(activeBuildings),
                        [&](Building* x){return find(begin(buildingsToRemove),end(buildingsToRemove),x)!=end(buildingsToRemove);}), end(activeBuildings) );

    for (const auto &item : buildingsToRemove) {
        delete item;
    }

    for (const auto &building : activeBuildings) {
        auto bdgloc = building->getXY();
        for (const auto &loc : building->getLocs()) {
            size_t i = static_cast<size_t>(bdgloc[0] + loc[0]);
            size_t j = static_cast<size_t>(bdgloc[1] + loc[1]);

            if (i < GRID_ROWS && j < GRID_COLS)
                buildings.at(i).at(j) = true;
        }
    }
    printBuildings();
}

void Game::populateBuilding(Building *building) {
    Point2d bdgloc = building->getXY();
    activeBuildings.push_back(building);
    for (const auto &loc : building->getLocs()) {
        size_t i = static_cast<size_t>(bdgloc[0] + loc[0]);
        size_t j = static_cast<size_t>(bdgloc[1] + loc[1]);

        buildings.at(i).at(j) = true;
    }
}

const std::vector<Building *> &Game::getActiveBuildings() const {
    return activeBuildings;
}

void Game::fillBuildings() {
    for (int i=0; i<GRID_ROWS; i++) {
        for (int j=0; j<GRID_COLS; j++) {
            buildings.at((size_t)i).at((size_t)j) = false;
        }
    }
}

