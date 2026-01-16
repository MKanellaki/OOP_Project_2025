#include "../include/selfDrivingCar.h"

SelfDrivingCar::SelfDrivingCar(int x, int y, CarDirection dir){
    speed = SpeedState::STOPPED;
    direction = dir;
    position = make_tuple(x,y);
    glyph = '@';
}

SelfDrivingCar::SelfDrivingCar(){
    speed = SpeedState::STOPPED;
    direction = CarDirection::NORTH;
    position = make_tuple(0,0);
    glyph = '@';
}

SelfDrivingCar::~SelfDrivingCar(){}

void SelfDrivingCar::set_speed(SpeedState spd){
    speed = spd;
}

void SelfDrivingCar::set_direction(CarDirection dir){
    direction = dir;
}

void SelfDrivingCar::set_position(int x, int y){
    position = make_tuple(x, y);
}

SpeedState SelfDrivingCar::get_speed() const{
    return speed;
}

CarDirection SelfDrivingCar::get_direction() const{
    return direction;
}

tuple<int, int> SelfDrivingCar::get_position() const{
    return position;
}

char SelfDrivingCar::get_glyph() const{
    return glyph;
}

void SelfDrivingCar::accelerate(){
    switch(speed){
        case SpeedState::STOPPED:
            speed = SpeedState::HALF_SPEED;
            break;
        case SpeedState::HALF_SPEED:
            speed = SpeedState::FULL_SPEED;
            break;
        case SpeedState::FULL_SPEED:
            break;
    }
}

void SelfDrivingCar::decelerate(){
    switch(speed){
        case SpeedState::FULL_SPEED:
            speed = SpeedState::HALF_SPEED;
            break;
        case SpeedState::HALF_SPEED:
            speed = SpeedState::STOPPED;
            break;
        case SpeedState::STOPPED:
            break;
    }
}

void SelfDrivingCar::move(){
    int step = 0;
    if (speed == SpeedState::HALF_SPEED) step = 1;
    if (speed == SpeedState::FULL_SPEED) step = 2;

    auto [x, y] = position;

    switch(direction){
        case CarDirection::NORTH: y += step; break;
        case CarDirection::SOUTH: y -= step; break;
        case CarDirection::EAST:  x += step; break;
        case CarDirection::WEST:  x -= step; break;
    }

    position = make_tuple(x, y);
}