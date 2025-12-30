#ifndef SENSORREADING_H
#define SENSORREADING_H

#include <tuple>
#include <string>
using namespace std;

enum class ObjectType{
    MOVING_CAR,
    MOVING_BIKE,
    PARKED_CAR,
    TRAFFIC_LIGHT,
    STOP_SIGN,
    SIGN
};

enum class TrafficLightColor{
    RED,
    YELLOW,
    GREEN
};

struct SensorReading{
    ObjectType type;
    int distance;
    tuple<int, int> position;
    string objectID;
    float confidence;
    int speed;
    string direction;
    string signText;
    TrafficLightColor trafficLight;
};

#endif