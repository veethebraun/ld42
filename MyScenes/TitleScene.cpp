//
// Created by vbrau on 8/12/2018.
//

#include "TitleScene.h"
#include "../GUI/Commands/PlayGameCommand.h"
#include "../GUI/Commands/HowToCommand.h"

void TitleScene::init() {
    drawables.push_back(createImageWidget(0,0,resourceManager->get_bitmap("title_scene")));

    drawables.push_back(createImageWidget(1190, 420, resourceManager->get_bitmap("play_button")));
    auto click = new Clickable(1190, 1190+501, 420, 420+230);
    click->setCommand(new PlayGameCommand());
    buttons.push_back(click);
    drawables.push_back(createImageWidget(1190, 720, resourceManager->get_bitmap("howto_button")));
    click = new Clickable(1190, 1190+501, 720, 720+230);
    click->setCommand(new HowToCommand());
    buttons.push_back(click);
}

void TitleScene::update(Game *game) {

}

void TitleScene::onSceneSwitch() {
    audioManager->play_music(resourceManager->get_audio_sample("bg_music"));
}
