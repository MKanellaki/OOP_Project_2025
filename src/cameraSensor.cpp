#include "../include/cameraSensor.h"
#include "../include/TrafficLights.h"
#include "../include/TrafficSigns.h"
#include <cmath>

using namespace std;

CameraSensor::CameraSensor() : Sensor(7, 0.95f) {}
CameraSensor::~CameraSensor() {}

vector<SensorReading> CameraSensor::scan(const GridWorld& world) {
    vector<SensorReading> readings;
    auto objects = world.get_GridWorld();

    int sx = get<0>(position);
    int sy = get<1>(position);

    for (auto* obj : objects) {
        int ox = obj->get_x_pos();
        int oy = obj->get_y_pos();

        int dx = ox - sx;
        int dy = oy - sy;

        // Square in front of vehicle
        bool visible = false;
        if (direction == CarDirection::NORTH && dy >= 0 && abs(dx) <= range && dy <= range) visible = true;
        if (direction == CarDirection::SOUTH && dy <= 0 && abs(dx) <= range && abs(dy) <= range) visible = true;
        if (direction == CarDirection::EAST  && dx >= 0 && dx <= range && abs(dy) <= range) visible = true;
        if (direction == CarDirection::WEST  && dx <= 0 && abs(dx) <= range && abs(dy) <= range) visible = true;

        if (!visible) continue;

        int distance = abs(dx) + abs(dy);
        if (distance > range) continue;

        readings.push_back(createReading(*obj, distance));
    }

    return readings;
}

bool CameraSensor::canDetect(const WorldObject&, int distance) const {
    return distance <= range;
}

SensorReading CameraSensor::createReading(const WorldObject& obj, int distance) const {
    SensorReading r;
    r.type = obj.getType();
    r.position = obj.getPosition();
    r.distance = distance;
    r.objectID = obj.getID();
    r.confidence = addNoise(accuracy * confidenceFromDistance(distance));

    // Camera reads everything
    r.speed = (r.type == ObjectType::MOVING_CAR) ? 2 :
              (r.type == ObjectType::MOVING_BIKE) ? 1 : -1;

    if (auto* moving = dynamic_cast<const MovingObjects*>(&obj)){
        if (moving->get_direction() == "left") r.direction = Direction::WEST;
        else if (moving->get_direction() == "right") r.direction = Direction::EAST;
        else if (moving->get_direction() == "up") r.direction = Direction::NORTH;
        else if (moving->get_direction() == "down") r.direction = Direction::SOUTH;
    }

    // Traffic light color
    if (r.type == ObjectType::TRAFFIC_LIGHT) {
        string g = obj.GET_glyph();
        if (g == "R") r.trafficLight = TrafficLightColor::RED;
        else if (g == "Y") r.trafficLight = TrafficLightColor::YELLOW;
        else if (g == "G") r.trafficLight = TrafficLightColor::GREEN;
    } else {
        r.trafficLight = TrafficLightColor::UNKNOWN;
    }

    // Sign text (simplified)
    if (r.type == ObjectType::STOP_SIGN)
        r.signText = "STOP";
    else
        r.signText = "N/A";

    return r;
}
