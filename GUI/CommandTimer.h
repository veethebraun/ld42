//
// Created by vbrau on 8/4/2018.
//

#ifndef LD42_VBRAUN_COMMANDTIMER_H
#define LD42_VBRAUN_COMMANDTIMER_H


#include <allegro5/timer.h>
#include "Commands/GameCommand.h"

class CommandTimer {
public:
    CommandTimer(double time, GameCommand *cmd);

    ALLEGRO_TIMER *getTimer() const;

    virtual ~CommandTimer();

    GameCommand *getCmd() const;

    ALLEGRO_EVENT_SOURCE* getEventSource() {
        return al_get_timer_event_source(timer);
    }

    void startTimer() {
        al_start_timer(timer);
    }
private:
    ALLEGRO_TIMER* timer;
    GameCommand* cmd;
};


#endif //LD42_VBRAUN_COMMANDTIMER_H
