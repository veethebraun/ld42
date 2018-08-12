//
// Created by vbrau on 8/12/2018.
//

#ifndef CLIMB_LOSESCREEN_H
#define CLIMB_LOSESCREEN_H


#include "../GUI/Scene.h"

class LoseScreen : public Scene {
public:
    explicit LoseScreen(ResourceManager *resourceManager, AudioStuff *audioManager) : Scene(resourceManager, audioManager) {};

    void init() override;
    void update(Game* game) override {};

    void onSceneSwitch() override;

};


#endif //CLIMB_LOSESCREEN_H
