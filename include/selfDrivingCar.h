#ifndef SELFDRIVINGCAR_H
#define SELFDRIVINGCAR_H

#include <iostream>
#include <tuple>
using namespace std;

enum class SpeedState{
    STOPPED,
    HALF_SPEED,
    FULL_SPEED
};

enum class Direction{
    NORTH,
    EAST,
    WEST,
    SOUTH
};

class SelfDrivingCar{
    private:
        SpeedState speed;
        Direction direction;
        tuple<int, int> position;
        char glyph;
    public:

        SelfDrivingCar(int x, int y, Direction dir);
        SelfDrivingCar();
        ~SelfDrivingCar();

        //setters
        void set_speed(SpeedState spd);
        void set_direction(Direction dir);
        void set_position(int x, int y);

        //getters
        SpeedState get_speed() const;
        Direction get_direction() const;
        tuple<int, int> get_position() const;

        void accelarate();
        void decelarate();
        void turn();
};

#endif