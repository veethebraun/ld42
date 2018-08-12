//
// Created by vbrau on 4/18/2018.
//

#include <iostream>
#include "Game.h"
#include "GUI/Commands/TileClickCommand.h"
#include "GUI/Commands/TimeTickCommand.h"
#include "GUI/Commands/SelectBuildingCommand.h"
#include "GUI/Commands/NewRowCommand.h"
#include "GUI/Commands/LaunchCommand.h"
#include "GUI/Commands/PlayGameCommand.h"
#include "GUI/Commands/HowToCommand.h"

GameCommand * Game::handleCommand(GameCommand *cmd) {
    if (current_scene == SceneList::TITLE || current_scene == SceneList::HOWTO)
    {
        auto play = dynamic_cast<PlayGameCommand*>(cmd);
        if (play != nullptr) {
            needToHandleClick = true;
            current_scene = SceneList ::GAME;
        }

        auto howto = dynamic_cast<HowToCommand*>(cmd);
        if (howto != nullptr) {
            needToHandleClick = true;
            current_scene = SceneList::HOWTO;
        }
    }

    if (current_scene == SceneList::WIN) {
        auto play = dynamic_cast<PlayGameCommand*>(cmd);
        if (play != nullptr) {
            needToHandleClick = true;
            for (const auto&building : activeBuildings) {
                delete building;
            }
            activeBuildings.clear();
            init();
            current_scene = SceneList ::GAME;
        }
    }

    if (current_scene == SceneList::GAME) {
        auto tile = dynamic_cast<TileClickCommand *>(cmd);
        if (tile != nullptr) {
            placeBuilding(tile->getI(), tile->getJ());
        }

        auto build = dynamic_cast<SelectBuildingCommand *>(cmd);
        if (build != nullptr) {
            currentBuildingSelection = build->getBuildingType();
            if (currentBuildingSelection == BuildingType::NONE) {
                message = "";
            }
        }

        auto time = dynamic_cast<TimeTickCommand *>(cmd);
        if (time != nullptr) {
            handleTimeTick();
        }

        auto newRow = dynamic_cast<NewRowCommand *>(cmd);
        if (newRow != nullptr) {
            addNewRow();
        }

        auto launch = dynamic_cast<LaunchCommand *>(cmd);
        if (launch != nullptr) {
            if (readyToLaunch)
                triggerWin();
        }
    }
    return nullptr;
}

void Game::init() {
    fillBuildings();
    current_scene = SceneList::TITLE;
    resource = new Resources();

    fillGrid(eligibleForBuild, true);
    buildingsFree = true;
    currentBuildingSelection = BuildingType ::MAT_STORAGE;
    placeBuilding(0,0);
    currentBuildingSelection = BuildingType ::WIND;
    placeBuilding(3,0);
    currentBuildingSelection = BuildingType ::MINE;
    placeBuilding(2,5);
    currentBuildingSelection = BuildingType ::STEEL;
    placeBuilding(4,4);
    buildingsFree = false;


    resource->resetResources();

    resource->addResources({WIND_POWER_GEN-MINE_POWER-STEEL_REFINERY_POWER,0,0,0,0});
    level = 0;
    dropCounter = 0;
    nextNewRow = -1;
    shrinkRow = 0;
}

SceneList Game::getCurrentScene() const {
    return current_scene;
}

void Game::clearAfterFrame() {
    needToHandleClick = false;
}

void Game::placeBuilding(int x, int y) {
    if (currentBuildingSelection != BuildingType::NONE) {
        auto building = buildingFactory.getNewBuilding(currentBuildingSelection, x, y);
        if (building->canBuild(resource) || buildingsFree) {
            if (doesBuildingFit(building)) {
                populateBuilding(building);
                building->onBuild(resource);
                if (currentBuildingSelection == BuildingType::ROCKET) {
                    readyToLaunch = true;
                }
                currentBuildingSelection = BuildingType::NONE;
                needToHandleClick = true;
                setMessage("");
            } else {
                setMessage("Bad Location");
            }
        } else {
            setMessage("Insufficient Resources");
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
        if (!eligibleForBuild.at((size_t) i).at((size_t)j))
            return false;

        if (building->getBuildingType() == BuildingType::MINE) {
            if (building->getX() == 0)
                return false;
        }
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

    std::vector<Building*> buildingsToRemove;
    for (const auto &building : activeBuildings) {
        building->dropLevel(resource);
        if (!building->isOnBoard(GRID_ROWS, GRID_COLS))
        {
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
            auto i = static_cast<size_t>(bdgloc[0] + loc[0]);
            auto j = static_cast<size_t>(bdgloc[1] + loc[1]);

            if (i < GRID_ROWS && j < GRID_COLS)
                buildings.at(i).at(j) = true;
        }
    }

    Grid newEligibility = {{{false}}};
    for (size_t i=1; i< GRID_ROWS; i++) {
        for (size_t j=0; j<GRID_COLS; j++) {
            newEligibility.at(i).at(j) = eligibleForBuild.at(i-1).at(j);
        }
    }

    eligibleForBuild = newEligibility;
    nextNewRow += 1;
    level++;
}

void Game::populateBuilding(Building *building) {
    Point2d bdgloc = building->getXY();
    activeBuildings.push_back(building);
    for (const auto &loc : building->getLocs()) {
        auto i = static_cast<size_t>(bdgloc[0] + loc[0]);
        auto j = static_cast<size_t>(bdgloc[1] + loc[1]);

        if (i < GRID_ROWS && j < GRID_COLS) {

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
    if (nextNewRow < 0 || nextNewRow >= GRID_ROWS || shrinkRow*2 >= GRID_COLS)
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

        for (auto j = (size_t)shrinkRow; j < GRID_COLS-shrinkRow; j++) {
            eligibleForBuild.at((size_t) nextNewRow).at(j) = true;
        }

        resource->addResources({0,0,-STEEL_FOR_NEW_ROW,0,0});
        nextNewRow -= 1;
    }

    shrinkRow = (level-nextNewRow)/SHRINK_COL_EVERY_N_ROWS;

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

int Game::getLevel() const {
    return level;
}

bool Game::isReadyToLaunch() const {
    return readyToLaunch;
}

void Game::triggerWin() {
    current_scene = SceneList ::WIN;
}

bool Game::closeToDrop() {
    return NUM_TIME_STEPS_FOR_DROP - dropCounter < NUM_TIME_STEPS_FOR_DROP/2;
}

bool Game::isNeedToHandleClick() const {
    return needToHandleClick;
}
