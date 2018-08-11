//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_TILECLICKCOMMAND_H
#define LD42_TILECLICKCOMMAND_H


#include "GameCommand.h"

class TileClickCommand : public GameCommand {
public:
    TileClickCommand(int i, int j) : i(i), j(j), GameCommand(i) {};
private:
    int i;
public:
    int getI() const {
        return i;
    }

    int getJ() const {
        return j;
    }

private:
    int j;
};


#endif //LD42_TILECLICKCOMMAND_H
