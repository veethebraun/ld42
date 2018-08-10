//
// Created by vbrau on 8/4/2018.
//

#ifndef LD42_VBRAUN_SCENEMANAGER_H
#define LD42_VBRAUN_SCENEMANAGER_H

#include <map>
#include "SceneList.h"
#include "Scene.h"
#include "AudioStuff.h"

class SceneManager {
public:
    explicit SceneManager(ResourceManager *resourceManager, AudioStuff *audioStuff);
    Scene* get(SceneList key);
    virtual ~SceneManager();

    Scene* switchScene(SceneList key);
private:
    std::map<SceneList, Scene*> scenes;
    SceneList currentScene = SceneList::NONE;

    template<typename T> void add_scene(SceneList key);

    ResourceManager* resourceManager;
    AudioStuff* audioStuff;
};


#endif //LD42_VBRAUN_SCENEMANAGER_H
