//
// Created by vbrau on 8/10/2018.
//

#include "GameScene.h"
#include "../GUI/Commands/TileClickCommand.h"
#include "../GameStuff/Building.h"
#include "../GUI/Commands/SelectBuildingCommand.h"

void GameScene::init() {
    background.push_back(createImageWidget(0,0,resourceManager->get_bitmap("game_bg")));
    background.push_back(createImageWidget(UI_START_PX,0,resourceManager->get_bitmap("game_ui_bg")));

    drawables.insert(drawables.end(), background.begin(), background.end());

    for (int i=0; i<TILE_COLUMNS; i++)
    {
        for (int j=0; j<TILE_ROWS; j++)
        {
            auto loc = gridLocationToPixel(i, j);
            auto tile = new Clickable(loc[0], loc[0] + TILE_SIZE_PX, loc[1], loc[1] + TILE_SIZE_PX);
            tile->setCommand(new TileClickCommand(j, i));
            buttons.push_back(tile);
        }
    }

    keybinds[ALLEGRO_KEY_M] = new SelectBuildingCommand(BuildingType::MINE);
    keybinds[ALLEGRO_KEY_W] = new SelectBuildingCommand(BuildingType::WIND);
    keybinds[ALLEGRO_KEY_S] = new SelectBuildingCommand(BuildingType::STEEL);
    keybinds[ALLEGRO_KEY_R] = new SelectBuildingCommand(BuildingType::MAT_STORAGE);
    keybinds[ALLEGRO_KEY_F] = new SelectBuildingCommand(BuildingType::FUEL);
    keybinds[ALLEGRO_KEY_G] = new SelectBuildingCommand(BuildingType::FUEL_STORAGE);
    keybinds[ALLEGRO_KEY_ESCAPE] = new SelectBuildingCommand(BuildingType::NONE);
}

void GameScene::update(Game *game) {
    drawables.clear();
    for (auto frameWidget : perFrameWidgets) {
        delete frameWidget;
    }
    perFrameWidgets.clear();


    auto bdg_bg = resourceManager->get_bitmap("tower_tile_bg");
    for (int i=0; i<TILE_COLUMNS; i++)
    {
        for (int j=0; j<TILE_ROWS; j++)
        {
            auto loc = gridLocationToPixel(i, j);
            perFrameWidgets.push_back(createImageWidget(loc[0], loc[1], bdg_bg));
        }
    }

    auto buildings = game->getActiveBuildings();
    for (const auto &building : buildings) {
        auto tile_bg = resourceManager->get_bitmap(building->getBitmapName().c_str());
        auto bdgcorner = building->getXY();

        for (const auto &bdgloc : building->getLocs()) {
            int i = bdgcorner[0] + bdgloc[0];
            int j = bdgcorner[1] + bdgloc[1];
            auto loc = gridLocationToPixel(j, i);
            perFrameWidgets.push_back(createImageWidget(loc[0], loc[1], tile_bg));
        }
    }

    updateResourceDisplay(game);

    drawables.insert(drawables.end(), background.begin(), background.end());
    drawables.insert(drawables.end(), perFrameWidgets.begin(), perFrameWidgets.end());

}

Point2d GameScene::gridLocationToPixel(int i, int j) {
    return Point2d({i*TILE_SIZE_PX + TILE_ROW_START_PX, j*TILE_SIZE_PX + TILE_COL_START_PX});
}

void GameScene::updateResourceDisplay(Game *game) {

    createResourceLine("Power: ", game->getResource()->getPower(), 0);
    createResourceLine("Raw Material: ", game->getResource()->getRawMaterial(), game->getResource()->getRawMaterialStorage(), 35);
    createResourceLine("Steel: ", game->getResource()->getSteel(), game->getResource()->getSteelStorage(), 70);
    createResourceLine("Fuel: ", game->getResource()->getFuel(), game->getResource()->getFuelStorage(), 105);
    createResourceLine("Life Support: ", game->getResource()->getLifeSupport(), 140);

    std::string selectedBuilding = "Building: ";
    selectedBuilding += getBuildingTypeStr(game->getCurrentBuildingSelection());
    auto txt = new Text(resourceManager->get_font("base_font"), 0, 0, selectedBuilding);
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font"), 0, 40, game->getMessage());
    perFrameWidgets.push_back(txt);
}

void GameScene::createResourceLine(const std::string &name, int value, int maxval, int height) {
    std::string valstr = std::to_string(value) + " / " + std::to_string(maxval) ;
    auto txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, height, name + valstr );
    txt->setColor(al_map_rgb(0,0,0));
    perFrameWidgets.push_back(txt);
}

void GameScene::createResourceLine(const std::string &name, int value, int height) {
    auto txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, height, name + std::to_string(value) );
    txt->setColor(al_map_rgb(0,0,0));
    perFrameWidgets.push_back(txt);
}
