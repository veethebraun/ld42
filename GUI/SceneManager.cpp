//
// Created by vbrau on 8/4/2018.
//

#include "SceneManager.h"

SceneManager::SceneManager(ResourceManager *resourceManager, AudioStuff *audioStuff) : resourceManager(resourceManager), audioStuff(audioStuff) {
    //add_scene<WinScreen>(SceneList::Win);
}

template<typename T>
void SceneManager::add_scene(SceneList key) {
    scenes[key] = new T(resourceManager, audioStuff);
    scenes[key]->init();
}

Scene *SceneManager::get(SceneList key) {
    return scenes[key];
}

SceneManager::~SceneManager() {
    for (const auto &item : scenes) {
        delete item.second;
    }
}

Scene *SceneManager::switchScene(SceneList key) {
    if (key != currentScene){
        currentScene = key;
        auto scene = get(key);
        scene->onSceneSwitch();
        return scene;
    }

    return get(key);
}
