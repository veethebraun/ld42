//
// Created by vbrau on 8/10/2018.
//

#include <iostream>
#include "GameScene.h"
#include "../GUI/Commands/TileClickCommand.h"
#include "../GUI/Commands/LaunchCommand.h"
#include "../GUI/Commands/SelectBuildingCommand.h"
#include "../GUI/Commands/NewRowCommand.h"
#include "../GUI/Widgets/SlowBitmapAnimation.h"

#define LAUNCH_BUTTON_X 90
#define LAUNCH_BUTTON_Y 800
#define LAUNCH_BUTTON_X_SIZE 501
#define LAUNCH_BUTTON_Y_SIZE 230
#define UI_FONT_SIZE 45
#define UI_FONT_SMALL_SIZE 35

void GameScene::init() {
    background.push_back(createImageWidget(0,0,resourceManager->get_bitmap("game_bg")));
    background.push_back(createImageWidget(UI_START_PX-5,0,resourceManager->get_bitmap("game_ui_bg")));

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
    hotkeyDescriptions["M"] = BuildingType::MINE;
    keybinds[ALLEGRO_KEY_W] = new SelectBuildingCommand(BuildingType::WIND);
    hotkeyDescriptions["W"] = BuildingType::WIND;
    keybinds[ALLEGRO_KEY_S] = new SelectBuildingCommand(BuildingType::STEEL);
    hotkeyDescriptions["S"] = BuildingType::STEEL;
    keybinds[ALLEGRO_KEY_R] = new SelectBuildingCommand(BuildingType::MAT_STORAGE);
    hotkeyDescriptions["R"] = BuildingType::MAT_STORAGE;
    keybinds[ALLEGRO_KEY_F] = new SelectBuildingCommand(BuildingType::FUEL);
    hotkeyDescriptions["F"] = BuildingType::FUEL;
    keybinds[ALLEGRO_KEY_G] = new SelectBuildingCommand(BuildingType::FUEL_STORAGE);
    hotkeyDescriptions["G"] = BuildingType::FUEL_STORAGE;
    keybinds[ALLEGRO_KEY_E] = new SelectBuildingCommand(BuildingType::ROCKET);
    hotkeyDescriptions["E"] = BuildingType::ROCKET;
    keybinds[ALLEGRO_KEY_N] = new NewRowCommand();
    keybinds[ALLEGRO_KEY_Q] = new SelectBuildingCommand(BuildingType::NONE);
}

void GameScene::update(Game *game) {
    if (game->isNeedToHandleClick())
    {
        audioManager->play_audio_fx(resourceManager->get_audio_sample("click"));
    }

    if (game->isPlayExplode())
    {
        audioManager->play_audio_fx(resourceManager->get_audio_sample("explode"));
    }

    drawables.clear();
    for (auto frameWidget : perFrameWidgets) {
        delete frameWidget;
    }
    perFrameWidgets.clear();

    if (game->getLevel() <= 3)
        perFrameWidgets.push_back(createImageWidget(0,(4+game->getLevel())*TILE_SIZE_PX + TILE_COL_START_PX+70, resourceManager->get_bitmap("ground")));

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
        auto bdgcorner = building->getXY();
        auto loc = gridLocationToPixel(bdgcorner[1], bdgcorner[0]);

        std::vector<std::string> stringFrames;
        stringFrames = BuildingFactory::getFrameNames(building->getBuildingType());
        if (stringFrames.size() == 1) {
            auto tile_bg = resourceManager->get_bitmap(stringFrames[0].c_str());
            perFrameWidgets.push_back(createImageWidget(loc[0], loc[1], tile_bg));
        } else if (stringFrames.size() > 1) {
            std::vector<ALLEGRO_BITMAP *> frames;
            frames.reserve(stringFrames.size());
            for (const auto &stringFrame : stringFrames) {
                frames.push_back(resourceManager->get_bitmap(stringFrame.c_str()));
            }

            int frameSpeed = BuildingFactory::getAnimSpeed(building->getBuildingType());
            auto anim = new SlowBitmapAnimation(loc[0], loc[1], frames, frameSpeed);
            if (!building->isDestroyed())
                anim->setFrameNum(frameNum);
            else
                anim->setFrameNum(0);

            perFrameWidgets.push_back(anim);
        }
    }

    if (!game->closeToDrop())
        perFrameWidgets.push_back(createImageWidget(0,(4)*TILE_SIZE_PX + TILE_COL_START_PX+70, resourceManager->get_bitmap("tentacles")));
    else
        perFrameWidgets.push_back(createImageWidget(0,(4)*TILE_SIZE_PX + TILE_COL_START_PX+70, resourceManager->get_bitmap("tentacles2")));


    updateResourceDisplay(game);


    if (game->getCurrentBuildingSelection() != BuildingType::NONE) {
        auto frames = BuildingFactory::getFrameNames(game->getCurrentBuildingSelection());
        perFrameWidgets.push_back(createImageWidget(currentMouseLoc[0]-TILE_SIZE_PX/2, currentMouseLoc[1]-TILE_SIZE_PX/2,
                resourceManager->get_bitmap(frames.front().c_str())));
    }

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
    UILine = 0;
    Text* txt;

    createResourceLine("Power: ", game->getResource()->getPower(), UI_FONT_SIZE*UILine++);
    createResourceLine("Raw Material: ", game->getResource()->getRawMaterial(), game->getResource()->getRawMaterialStorage(), UI_FONT_SIZE*UILine++);
    createResourceLine("Steel: ", game->getResource()->getSteel(), game->getResource()->getSteelStorage(), UI_FONT_SIZE*UILine++);
    createResourceLine("Fuel: ", game->getResource()->getFuel(), game->getResource()->getFuelStorage(), UI_FONT_SIZE*UILine++);

    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "");
    perFrameWidgets.push_back(txt);
    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "");
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "Press <KEY> to Build:");
    perFrameWidgets.push_back(txt);

    for (const auto &hotkeyDescription : hotkeyDescriptions) {
        createShortcutLine(hotkeyDescription, UI_FONT_SIZE*UILine++);
    }
    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "Q: Deselect Building");
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "N: Build Next Level (Costs " + std::to_string(STEEL_FOR_NEW_ROW) + " steel)");
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, UI_FONT_SIZE*UILine++, "ESC: Quit Game");
    perFrameWidgets.push_back(txt);

    UILine = 0;
    std::string selectedBuilding = "Building: ";
    selectedBuilding += getBuildingTypeStr(game->getCurrentBuildingSelection());
    txt = new Text(resourceManager->get_font("base_font2"), 0, UI_FONT_SMALL_SIZE*UILine++, selectedBuilding);
    txt->setColor(al_map_rgb(0,120,255));
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font2"), 0, UI_FONT_SMALL_SIZE*UILine++, getRequiredText(BuildingFactory::getCosts(game->getCurrentBuildingSelection())));
    txt->setColor(al_map_rgb(0,120,255));
    perFrameWidgets.push_back(txt);
    txt = new Text(resourceManager->get_font("base_font2"), 0, UI_FONT_SMALL_SIZE*UILine++, BuildingFactory::getProvides(game->getCurrentBuildingSelection()));
    txt->setColor(al_map_rgb(0,120,255));
    perFrameWidgets.push_back(txt);

    txt = new Text(resourceManager->get_font("base_font2"), 0, UI_FONT_SMALL_SIZE*UILine++, game->getMessage());
    txt->setColor(al_map_rgb(255,0,0));
    perFrameWidgets.push_back(txt);

    if (game->isReadyToLaunch()) {
        std::vector<ALLEGRO_BITMAP*> frames;
        frames.push_back(resourceManager->get_bitmap("active_launch_button_f1"));
        frames.push_back(resourceManager->get_bitmap("active_launch_button_f2"));
        auto anim = new SlowBitmapAnimation(LAUNCH_BUTTON_X + UI_START_PX, LAUNCH_BUTTON_Y, frames, 8);
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
    if (value < 0)
        txt->setColor(al_map_rgb(255,0,0));
    else
        txt->setColor(al_map_rgb(0,0,0));
    perFrameWidgets.push_back(txt);
}

void GameScene::onSceneSwitch() {
}

std::string GameScene::getRequiredText(std::valarray<int> inCost) {
    std::string out;
    std::array<std::string,5> resources = {"Power", "Raw Material", "Steel", "Fuel", "Life Support"};
    for (size_t i=0;i<5;i++) {
        if (inCost[i] > 0)
            out += resources[i] + ": " + std::to_string(inCost[i]) + " ";
    }
    if (out.length() > 0){
        out = "Requires - " + out;
    }
    return out;
}

void GameScene::createShortcutLine(std::pair<std::string, BuildingType> inPair, int xPos) {
    auto txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, xPos,
            inPair.first + ": " + getBuildingTypeStr(inPair.second) );
    perFrameWidgets.push_back(txt);
}
