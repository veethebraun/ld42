//
// Created by vbrau on 8/10/2018.
//

#ifndef LD42_BUILDING_H
#define LD42_BUILDING_H


class Building {
public:
    Building(int x, int y, int x_size, int y_size) : x(x), y(y), x_size(x_size), y_size(y_size) {};

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getX_size() const {
        return x_size;
    }

    int getY_size() const {
        return y_size;
    }

    int output_resources();

private:
    int x;
    int y;

    int x_size;
    int y_size;
};


#endif //LD42_BUILDING_H
