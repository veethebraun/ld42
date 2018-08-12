//
// Created by vbrau on 4/18/2018.
//

#ifndef LD42_VBRAUN_SCENE_H
#define LD42_VBRAUN_SCENE_H

#include "Widgets/Widget.h"
#include "Widgets/Clickable.h"
#include "Widgets/Button.h"
#include "Widgets/Text.h"
#include "../Game.h"
#include "Widgets/ImageWidget.h"
#include "Widgets/Animation.h"
#include "Resources/ResourceManager.h"
#include "AudioStuff.h"
#include "Widgets/BitmapAnimation.h"
#include <vector>
#include <map>
#include <queue>

class Scene {
protected:
    std::map<int,GameCommand*> keybinds;

    Button * createButtonWithText(int x1, int x2, int y1, int y2,const std::string &text);
    Text * createText(int x, int y, const std::string &text);
    ImageWidget* createImageWidget(int x, int y, ALLEGRO_BITMAP *bitmap);

    std::vector<Widget*> drawables;
    ResourceManager* resourceManager;
    AudioStuff* audioManager;
    std::vector<Clickable*> buttons;
    std::vector<BitmapAnimation*> animations;
public:
    explicit Scene(ResourceManager *resourceManager, AudioStuff *audioManager);
    virtual void init() = 0;

    void setAnimations();

    std::queue<GameCommand*> onKeyboardPress(ALLEGRO_EVENT event);
    std::queue<GameCommand*> onMousePress(ALLEGRO_EVENT event);

    virtual void onSceneSwitch() {};

    virtual void update(Game* game) = 0;
    void draw();

    void incrementFrame();
    virtual ~Scene() = default;
};


#endif //LD42_VBRAUN_SCENE_H
