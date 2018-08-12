//
// Created by vbrau on 8/10/2018.
//

#include <iostream>
#include "GameScene.h"
#include "../GUI/Commands/TileClickCommand.h"
#include "../GameStuff/Building.h"
#include "../GUI/Commands/SelectBuildingCommand.h"
#include "../GUI/Commands/NewRowCommand.h"
#include "../GUI/Widgets/SlowBitmapAnimation.h"
#include "../GUI/Commands/LaunchCommand.h"

#define LAUNCH_BUTTON_X 90
#define LAUNCH_BUTTON_Y 800
#define LAUNCH_BUTTON_X_SIZE 501
#define LAUNCH_BUTTON_Y_SIZE 230

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

    auto launch = new Clickable(LAUNCH_BUTTON_X + UI_START_PX, LAUNCH_BUTTON_X + LAUNCH_BUTTON_X_SIZE + UI_START_PX,
            LAUNCH_BUTTON_Y, LAUNCH_BUTTON_Y + LAUNCH_BUTTON_Y_SIZE);
    launch->setCommand(new LaunchCommand());
    buttons.push_back(launch);

    keybinds[ALLEGRO_KEY_M] = new SelectBuildingCommand(BuildingType::MINE);
    keybinds[ALLEGRO_KEY_W] = new SelectBuildingCommand(BuildingType::WIND);
    keybinds[ALLEGRO_KEY_S] = new SelectBuildingCommand(BuildingType::STEEL);
    keybinds[ALLEGRO_KEY_R] = new SelectBuildingCommand(BuildingType::MAT_STORAGE);
    keybinds[ALLEGRO_KEY_F] = new SelectBuildingCommand(BuildingType::FUEL);
    keybinds[ALLEGRO_KEY_G] = new SelectBuildingCommand(BuildingType::FUEL_STORAGE);
    keybinds[ALLEGRO_KEY_E] = new SelectBuildingCommand(BuildingType::ROCKET);
    keybinds[ALLEGRO_KEY_N] = new NewRowCommand();
    keybinds[ALLEGRO_KEY_ESCAPE] = new SelectBuildingCommand(BuildingType::NONE);
}

void GameScene::update(Game *game) {
    drawables.clear();
    for (auto frameWidget : perFrameWidgets) {
        delete frameWidget;
    }
    perFrameWidgets.clear();

    if (game->getLevel() <= 3)
        perFrameWidgets.push_back(createImageWidget(0,(4+game->getLevel())*TILE_SIZE_PX + TILE_COL_START_PX+70, resourceManager->get_bitmap("ground")));

//    for (auto anim : animations) {
//        delete anim;
//    }
    animations.clear();

    auto bdg_bg = resourceManager->get_bitmap("tower_tile_bg");
    for (int i=0; i<TILE_COLUMNS; i++)
    {
        for (int j=TILE_ROWS + game->getLevel(); j>=0; j--)
        {
            if (j < TILE_ROWS) {
                if (game->buildableAt((size_t) j, (size_t) i)) {
                    auto loc = gridLocationToPixel(i, j);
                        perFrameWidgets.push_back(
                                createImageWidget(loc[0], loc[1], bdg_bg)); // 27 for offset in tile_bg
                }
            } else if (j >= TILE_ROWS && game->getLevel() > 0)
            {
                auto loc = gridLocationToPixel(i, j);
                if (loc[1] <= 1100)
                    perFrameWidgets.push_back(
                            createImageWidget(loc[0], loc[1], bdg_bg)); // 27 for offset in tile_bg
            }
        }
    }

    auto buildings = game->getActiveBuildings();
    for (const auto &building : buildings) {
        auto tile_bg = resourceManager->get_bitmap(building->getBitmapName().c_str());
        auto bdgcorner = building->getXY();
        auto loc = gridLocationToPixel(bdgcorner[1], bdgcorner[0]);
        if (building->getBitmapName() == "wind_power") {
            std::vector<ALLEGRO_BITMAP*> frames;
            frames.push_back(resourceManager->get_bitmap("wind_power_f1"));
            frames.push_back(resourceManager->get_bitmap("wind_power_f2"));
            frames.push_back(resourceManager->get_bitmap("wind_power_f3"));
            frames.push_back(resourceManager->get_bitmap("wind_power_f4"));
            frames.push_back(resourceManager->get_bitmap("wind_power_f5"));
            auto anim = new SlowBitmapAnimation(loc[0], loc[1], frames, 2);
            if (!building->isDestroyed())
                anim->setFrameNum(frameNum);
            else
                anim->setFrameNum(0);
            animations.push_back(anim);
            perFrameWidgets.push_back(anim);

        } else {
            perFrameWidgets.push_back(createImageWidget(loc[0], loc[1], tile_bg));
        }
        //
//        for (const auto &bdgloc : building->getLocs()) {
//            int i = bdgcorner[0] + bdgloc[0];
//            int j = bdgcorner[1] + bdgloc[1];
//            auto loc = gridLocationToPixel(j, i);
//            perFrameWidgets.push_back(createImageWidget(loc[0], loc[1], tile_bg));
//        }
    }

    perFrameWidgets.push_back(createImageWidget(0,(4)*TILE_SIZE_PX + TILE_COL_START_PX+70, resourceManager->get_bitmap("tentacles")));

    updateResourceDisplay(game);

    drawables.insert(drawables.end(), background.begin(), background.end());

    drawables.insert(drawables.end(), perFrameWidgets.begin(), perFrameWidgets.end());

    frameNum++;
    if (frameNum == INT16_MAX)
        frameNum = 0;
}

Point2d GameScene::gridLocationToPixel(int i, int j) {
    return Point2d({i*TILE_SIZE_PX + TILE_ROW_START_PX, j*TILE_SIZE_PX + TILE_COL_START_PX - 27});
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

    if (game->isReadyToLaunch()) {
        std::vector<ALLEGRO_BITMAP*> frames;
        frames.push_back(resourceManager->get_bitmap("active_launch_button_f1"));
        frames.push_back(resourceManager->get_bitmap("active_launch_button_f2"));
        auto anim = new SlowBitmapAnimation(LAUNCH_BUTTON_X + UI_START_PX, LAUNCH_BUTTON_Y, frames, 5);
        anim->setFrameNum(frameNum);
        perFrameWidgets.push_back(anim);
    } else {
        auto launch = createImageWidget(LAUNCH_BUTTON_X + UI_START_PX, LAUNCH_BUTTON_Y, resourceManager->get_bitmap("dis_launch_button"));
        perFrameWidgets.push_back(launch);
    }
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

void GameScene::onSceneSwitch() {
    audioManager->play_music(resourceManager->get_audio_sample("bg_music"));
}
