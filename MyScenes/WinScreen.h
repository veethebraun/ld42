//
// Created by vbrau on 8/12/2018.
//

#ifndef CLIMB_WINSCREEN_H
#define CLIMB_WINSCREEN_H


#include "../GUI/Scene.h"

class WinScreen : public Scene {
public:
    explicit WinScreen(ResourceManager *resourceManager, AudioStuff *audioManager) : Scene(resourceManager, audioManager) {};

    void init() override;
    void update(Game* game) override;

    void onSceneSwitch() override;

};


#endif //CLIMB_WINSCREEN_H
