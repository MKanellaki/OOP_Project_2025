#include "../include/sensor.h"

using namespace std;

Sensor::Sensor(int r, float acc)
    : range(r), position({0,0}), accuracy(acc), direction(CarDirection::NORTH){}

Sensor::~Sensor(){}

void Sensor::updatePosition(int x, int y){
    position = make_tuple(x, y);
}

void Sensor::updateDirection(CarDirection dir){
    direction = dir;
}

float Sensor::confidenceFromDistance(int distance) const{
    if(distance > range){
        return 0.0f;
    }
    return 1.0f - (float(distance) / float(range));
}

float Sensor::addNoise(float confidence) const{
    float noise = ((rand() % 100) / 1000.0f) - 0.05f; //[-0.05, +0.05]
    float noisy = confidence + noise;
    if (noisy < 0.0f) noisy = 0.0f;
    if (noisy > 1.0f) noisy = 1.0f;
    return noisy;
}