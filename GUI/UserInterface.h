//
// Created by vbrau on 4/15/2018.
//

#ifndef LD42_VBRAUN_USERINTERFACE_H
#define LD42_VBRAUN_USERINTERFACE_H


#include "../Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Resources/ResourceManager.h"
#include "CommandTimer.h"
#include "AudioStuff.h"
#include <vector>
#include <map>

class UserInterface {
private:
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_DISPLAY *window;

    Game* game;

    Scene* current_scene;
    ResourceManager* resourceManager;
    SceneManager* sceneManager;
    std::vector<CommandTimer*> timers;
    CommandTimer* graphics_timer;
    AudioStuff* audioManager;
public:
    virtual ~UserInterface();

    UserInterface();

    void init();

    void run();
};


#endif //LD42_VBRAUN_USERINTERFACE_H
