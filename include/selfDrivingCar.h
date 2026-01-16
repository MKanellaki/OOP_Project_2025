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

enum class CarDirection{
    NORTH,
    EAST,
    WEST,
    SOUTH,
};

class SelfDrivingCar{
    private:
        SpeedState speed;
        CarDirection direction;
        tuple<int, int> position;
        char glyph;
    public:

        SelfDrivingCar(int x, int y, CarDirection dir);
        SelfDrivingCar();
        ~SelfDrivingCar();

        //setters
        void set_speed(SpeedState spd);
        void set_direction(CarDirection dir);
        void set_position(int x, int y);

        //getters
        SpeedState get_speed() const;
        CarDirection get_direction() const;
        tuple<int, int> get_position() const;
        char get_glyph() const;

        void accelerate();
        void decelerate();
        
        void move();
};

#endif