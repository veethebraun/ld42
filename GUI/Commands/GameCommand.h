//
// Created by vbrau on 4/17/2018.
//

#ifndef LD42_VBRAUN_COMMAND_H
#define LD42_VBRAUN_COMMAND_H


class GameCommand {
private:
    int data;
public:
    int getData() const;
    virtual ~GameCommand() = default;
    virtual void print();

public:
    explicit GameCommand(int data);
};


#endif //LD42_VBRAUN_COMMAND_H
