//
// Created by vbrau on 4/17/2018.
//

#include <iostream>
#include "GameCommand.h"

GameCommand::GameCommand(int data) : data(data) {}

int GameCommand::getData() const {
    return data;
}

void GameCommand::print() {
    //std::cout << "Base GameCommand.." << std::endl;
}
