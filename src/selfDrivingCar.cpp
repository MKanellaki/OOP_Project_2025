#include "include/selfDrivingCar.h"

SelfDrivingCar::SelfDrivingCar(int x, int y, Direction dir){
    speed = SpeedState::STOPPED;
    direction = dir;
    position = make_tuple(x,y);
    glyph = '@';
}

SelfDrivingCar::SelfDrivingCar(){
    speed = SpeedState::STOPPED;
    direction = Direction::NORTH;
    position = make_tuple(0,0);
    glyph = '@';
}


void SelfDrivingCar::set_speed(SpeedState spd){
    speed = spd;
}

void SelfDrivingCar::set_direction(Direction dir){
    direction = dir;
}

void SelfDrivingCar::set_position(int x, int y){
    position = make_tuple(x, y);
}

SpeedState SelfDrivingCar::get_speed() const{
    return speed;
}

Direction SelfDrivingCar::get_direction() const{
    return direction;
}

tuple<int, int> SelfDrivingCar::get_position() const{
    return position;
}

void SelfDrivingCar::accelarate(){
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

void SelfDrivingCar::decelarate(){
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