//
// Created by vbrau on 4/18/2018.
//

#include <iostream>
#include "Game.h"
#include "GUI/Commands/TileClickCommand.h"
#include "GUI/Commands/TimeTickCommand.h"
#include "GUI/Commands/SelectBuildingCommand.h"
#include "GUI/Commands/NewRowCommand.h"

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

    auto newRow = dynamic_cast<NewRowCommand*>(cmd);
    if (newRow != nullptr) {
        addNewRow();
    }
    return nullptr;
}

void Game::init() {
    fillBuildings();
    current_scene = SceneList::GAME;
    resource = new Resources();

    fillGrid(eligibleForBuild, true);
    printEligibleBuildings();
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

        std::cout <<"A";
        if (i < 0 || i >= GRID_ROWS || j < 0 || j >= GRID_COLS)
            return false;
        std::cout <<"B";
        if (hasBuilding(i, j))
            return false;
        std::cout <<"C" << i << j;
        if (!eligibleForBuild.at((size_t) i).at((size_t)j))
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

    Grid newEligibility = {{{false}}};
    for (size_t i=1; i< GRID_ROWS; i++) {
        for (size_t j=0; j<GRID_COLS; j++) {
            newEligibility.at(i).at(j) = eligibleForBuild.at(i-1).at(j);
        }
    }

    eligibleForBuild = newEligibility;
    nextNewRow += 1;
}

void Game::populateBuilding(Building *building) {
    Point2d bdgloc = building->getXY();
    activeBuildings.push_back(building);
    for (const auto &loc : building->getLocs()) {
        size_t i = static_cast<size_t>(bdgloc[0] + loc[0]);
        size_t j = static_cast<size_t>(bdgloc[1] + loc[1]);

        if (i < GRID_ROWS && j < GRID_COLS) {

            std::cout << "D" << i << j;
            buildings.at(i).at(j) = true;
        }
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

bool Game::buildableAt(size_t i, size_t j) {
    return eligibleForBuild.at(i).at(j);
}

void Game::addNewRow() {
    if (nextNewRow < 0 || nextNewRow >= GRID_ROWS)
        return;
    bool good = false;
    for (const auto &item : eligibleForBuild.at((size_t)nextNewRow)) {
        if (!item) {
            good = true;
            break;
        }
    }

    if (!good)
        return;

    if (resource->getSteel() > STEEL_FOR_NEW_ROW || buildingsFree) {

        for (size_t j = 0; j < GRID_COLS; j++) {
            eligibleForBuild.at((size_t) nextNewRow).at(j) = true;
        }
        nextNewRow -= 1;
    }

}

void Game::fillGrid(Grid &grid, bool val) {
    for (size_t i=0; i<GRID_ROWS; i++) {
        for (size_t j = 0; j < GRID_COLS; j++) {
            grid.at(i).at(j) = val;
        }
    }
}

void Game::printEligibleBuildings() {
    for (size_t i=0; i<GRID_ROWS; i++){
        for (size_t j=0; j<GRID_COLS; j++) {
            std::cout << (eligibleForBuild.at(i).at(j));
        }
        std::cout << std::endl;
    }
}
