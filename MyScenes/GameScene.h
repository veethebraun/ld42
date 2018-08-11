//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_GAMESCENE_H
#define LD42_GAMESCENE_H

#include "../GUI/Scene.h"
#include "../vectors.h"

#define TILE_SIZE_PX 135
#define UI_START_PX 1185

#define TILE_ROWS 5
#define TILE_COLUMNS 7
#define TILE_ROW_START_PX 120
#define TILE_COL_START_PX 202


class GameScene : public Scene {
public:
    explicit GameScene(ResourceManager *resourceManager, AudioStuff *audioManager) : Scene(resourceManager, audioManager) {};

    void init() override;
    void update(Game* game) override;

private:
    std::vector<Widget*> background;
    std::vector<Widget*> perFrameWidgets;

    Vector2d<int> gridLocationToPixel(int i, int j);

    void updateResourceDisplay(Game* game);

    void createResourceLine(std::string name, int value, int height);
    void createResourceLine(std::string name, int value, int maxval, int height);

};


#endif //LD42_GAMESCENE_H
