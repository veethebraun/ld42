//
// Created by vbrau on 8/12/2018.
//

#include "WinScreen.h"
#include "../GUI/Commands/PlayGameCommand.h"

void WinScreen::init() {
    drawables.push_back(createImageWidget(0,0,resourceManager->get_bitmap("win_screen")));
    drawables.push_back(createImageWidget(1000, 700, resourceManager->get_bitmap("play_button")));
    auto click = new Clickable(1000, 1000+501, 700, 700+230);
    click->setCommand(new PlayGameCommand());
    buttons.push_back(click);

    auto txt = new Text(resourceManager->get_font("base_font"),990, 1025, "Hit the Escape Key to QUIT");
    txt->setColor(al_map_rgb(255,255,255));
    drawables.push_back(txt);
}

void WinScreen::update(Game *game) {

}

void WinScreen::onSceneSwitch() {
    Scene::onSceneSwitch();
}
