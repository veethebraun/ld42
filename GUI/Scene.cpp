//
// Created by vbrau on 4/18/2018.
//

#include "Scene.h"
#include "Widgets/WidgetComposition.h"
#include "Widgets/FilledRectangle.h"
#include "Widgets/Animation.h"

Scene::Scene(ResourceManager *resourceManager, AudioStuff *audioManager) : resourceManager(resourceManager), audioManager(audioManager) {
}

Button *Scene::createButtonWithText(int x1, int x2, int y1, int y2, const std::string &text) {
    auto widget_group = new WidgetComposition();

    auto bg = new FilledRectangle(x1, y1, x2, y2, al_map_rgb(0,0,124));
    widget_group->addWidget(bg);
    drawables.push_back(bg);

    auto textbox = new Text(resourceManager->get_font("main_font"), x1, y1, text);
    textbox->setColor(al_map_rgb(250,0,0));
    widget_group->addWidget(textbox);
    drawables.push_back(textbox);

    auto button = new Button(x1, x2, y1, y2, widget_group);
    buttons.push_back(button);

    return button;
}

Text *Scene::createText(int x, int y, const std::string &text) {
    auto textbox = new Text(resourceManager->get_font("main_font"), x, y, text);

    drawables.push_back(textbox);
    return textbox;
}

std::queue<GameCommand *> Scene::onKeyboardPress(ALLEGRO_EVENT event) {
    std::queue<GameCommand *> command_queue;
    auto search = keybinds.find(event.keyboard.keycode);
    if (search != keybinds.end()) {
        command_queue.push( search->second );
    }
    return command_queue;
}

std::queue<GameCommand *> Scene::onMousePress(ALLEGRO_EVENT event) {
    std::queue<GameCommand *> command_queue;
    for (auto &&item : buttons) {
        if (item->withinBox(event.mouse.x, event.mouse.y)) {
            auto possible_command = item->onClick();
            if (possible_command != nullptr) {
                command_queue.push(possible_command);
            }
        }
    }
    return command_queue;
}

void Scene::draw() {
    for (auto &&drawable : drawables) {
        drawable->draw();
    }
}

ImageWidget *Scene::createImageWidget(int x, int y, ALLEGRO_BITMAP *bitmap) {
    auto img = new ImageWidget(x, y, bitmap);
    //drawables.push_back(img);
    return img;
}

void Scene::incrementFrame() {
    for (auto &&anim : animations) {
        anim->incrementFrame();
    }
}

void Scene::setAnimations() {
//    for (auto &&drawable : drawables) {
//        auto animation = dynamic_cast<Animation*>(drawable);
//        if (animation != nullptr)
//        {
//            animations.push_back(animation);
//        }
//    }
}
