//
// Created by vbrau on 8/12/2018.
//

#include "HowToScene.h"
#include "../GUI/Commands/PlayGameCommand.h"

void HowToScene::init() {
    drawables.push_back(createImageWidget(0,0,resourceManager->get_bitmap("howto_screen")));

    drawables.push_back(createImageWidget(1190+90, 800, resourceManager->get_bitmap("play_button")));
    auto click = new Clickable(90+1190, 1190+501+90, 800, 800+230);
    click->setCommand(new PlayGameCommand());
    buttons.push_back(click);
}

void HowToScene::update(Game *game) {

}

void HowToScene::onSceneSwitch() {
    Scene::onSceneSwitch();
}
