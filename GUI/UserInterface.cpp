//
// Created by vbrau on 4/15/2018.
//

#include <iostream>
#include "UserInterface.h"
#include "allegro5/allegro.h"
#include <queue>

void UserInterface::init() {
    resourceManager = new ResourceManager("cfg/fonts.yaml", "cfg/bitmaps.yaml", "cfg/audio.yaml");
    audioManager = new AudioStuff();
    audioManager->init();

    event_queue = al_create_event_queue();

    graphics_timer = new CommandTimer(1.0/20.0, nullptr);
    timers.push_back(graphics_timer);

    al_register_event_source(event_queue, al_get_keyboard_event_source() );
    al_register_event_source(event_queue, al_get_mouse_event_source() );
    for (const auto &item : timers) {
        al_register_event_source(event_queue, item->getEventSource());
    }

    window = al_create_display(1000,1000);

    game = new Game();
    game->init();

    sceneManager = new SceneManager(resourceManager, audioManager);
    current_scene = sceneManager->switchScene(game->getCurrentScene());
    current_scene->update(game);

    al_set_target_backbuffer(window);
    current_scene->draw();
    al_flip_display();
}

void UserInterface::run() {
    for (const auto &item : timers) {
        item->startTimer();
    }

    bool shouldDraw = false;
    std::queue<GameCommand*> command_queue;
    while (true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_Q) {
                break;
            }
            command_queue = current_scene->onKeyboardPress(event);
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            command_queue = current_scene->onMousePress(event);
        }

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
            for (const auto &item : timers) {
                if (item->getTimer() == event.timer.source && item->getCmd() != nullptr)
                    command_queue.push(item->getCmd());
            }
            if (event.timer.source == graphics_timer->getTimer()) {
                current_scene->incrementFrame();
                shouldDraw = true;
            }
        }

        std::queue<GameCommand*> game_commands;
        while (!command_queue.empty()) {
            GameCommand *cmd = command_queue.front();
            auto return_cmd = game->handleCommand(cmd);
            command_queue.pop();
            if (return_cmd != nullptr)
                game_commands.push(return_cmd);
        }

        while(!game_commands.empty())
        {
            command_queue.push(game_commands.front());
            game_commands.pop();
        }

        current_scene = sceneManager->switchScene(game->getCurrentScene());

        if (shouldDraw) {
            current_scene->update(game);
            game->clearAfterFrame();

            al_set_target_backbuffer(window);
            al_clear_to_color(al_map_rgb(255, 255, 255));
            current_scene->draw();

            al_flip_display();
            shouldDraw = false;
        }
    }
}

UserInterface::UserInterface() = default;

UserInterface::~UserInterface() {
    delete resourceManager;

    al_destroy_display(window);
    al_destroy_event_queue(event_queue);
}

