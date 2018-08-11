//
// Created by vbrau on 8/10/2018.
//

#include "GameScene.h"
#include "../GUI/Commands/TileClickCommand.h"
#include "../GameStuff/Building.h"

void GameScene::init() {
    background.push_back(createImageWidget(0,0,resourceManager->get_bitmap("game_bg")));
    background.push_back(createImageWidget(UI_START_PX,0,resourceManager->get_bitmap("game_ui_bg")));

    drawables.insert(drawables.end(), background.begin(), background.end());

    for (int i=0; i<TILE_COLUMNS; i++)
    {
        for (int j=0; j<TILE_ROWS; j++)
        {
            auto loc = gridLocationToPixel(i, j);
            auto tile = new Clickable(loc.x, loc.x + TILE_SIZE_PX, loc.y, loc.y + TILE_SIZE_PX);
            tile->setCommand(new TileClickCommand(j, i));
            buttons.push_back(tile);
        }
    }
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
            perFrameWidgets.push_back(createImageWidget(loc.x, loc.y, bdg_bg));
        }
    }

    auto buildings = game->getBuildingToGrid();
    auto tile_bg = resourceManager->get_bitmap("base_tile");
    for (const auto &building : buildings) {
        auto bdgloc = building.second;

        for (int i=bdgloc.x; i<bdgloc.x + building.first->getX_size(); i++) {
            for (int j = bdgloc.y; j < bdgloc.y + building.first->getY_size(); j++) {
                auto loc = gridLocationToPixel(j, i);
                perFrameWidgets.push_back(createImageWidget(loc.x, loc.y, tile_bg));
            }
        }
    }

    std::string resStr = "Resource:";
    resStr += std::to_string(game->getResource());
    auto txt = new Text(resourceManager->get_font("base_font"), UI_START_PX, 0, resStr);
    txt->setColor(al_map_rgb(0,0,0));

    perFrameWidgets.push_back(txt);

    drawables.insert(drawables.end(), background.begin(), background.end());
    drawables.insert(drawables.end(), perFrameWidgets.begin(), perFrameWidgets.end());

}

Vector2d<int> GameScene::gridLocationToPixel(int i, int j) {
    Vector2d<int> out;

    out.x = i*TILE_SIZE_PX + TILE_ROW_START_PX;
    out.y = j*TILE_SIZE_PX + TILE_COL_START_PX;

    return out;
}
