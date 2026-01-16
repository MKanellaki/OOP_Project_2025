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
    GREEN,
    UNKNOWN
};

enum class Direction{
    NORTH,
    EAST,
    WEST,
    SOUTH,
    UNKNOWN
};

struct SensorReading{
    ObjectType type; //lidar
    int distance; //lidar,radar
    tuple<int, int> position;
    string objectID;
    float confidence; //lidar,radar
    int speed; //radar
    Direction direction; //radar
    string signText;//camera
    TrafficLightColor trafficLight;//camera
};

#endif