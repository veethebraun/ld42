//
// Created by vbrau on 8/12/2018.
//

#ifndef CLIMB_TITLESCENE_H
#define CLIMB_TITLESCENE_H


#include "../GUI/Scene.h"

class TitleScene : public Scene {
public:
    explicit TitleScene(ResourceManager *resourceManager, AudioStuff *audioManager) : Scene(resourceManager, audioManager) {};

    void init() override;
    void update(Game* game) override;

    void onSceneSwitch() override;
};


#endif //CLIMB_TITLESCENE_H
