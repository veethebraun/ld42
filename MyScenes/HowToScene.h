//
// Created by vbrau on 8/12/2018.
//

#ifndef CLIMB_HOWTOSCENE_H
#define CLIMB_HOWTOSCENE_H


#include "../GUI/Scene.h"

class HowToScene : public Scene {
public:
    explicit HowToScene(ResourceManager *resourceManager, AudioStuff *audioManager) : Scene(resourceManager, audioManager) {};

    void init() override;
    void update(Game* game) override;

    void onSceneSwitch() override;
};


#endif //CLIMB_HOWTOSCENE_H
