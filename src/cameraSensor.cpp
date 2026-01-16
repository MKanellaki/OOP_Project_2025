#include "../include/cameraSensor.h"
#include "../include/TrafficLights.h"
#include "../include/TrafficSigns.h"
#include <cmath>

using namespace std;

CameraSensor::CameraSensor() : Sensor(7, 0.95f) {}

vector<SensorReading> CameraSensor::scan(const GridWorld& world) {
    vector<SensorReading> readings;
    auto objects = world.get_GridWorld();

    int sx = get<0>(position);
    int sy = get<1>(position);

    for(auto* obj : objects){
        int ox = obj->get_x_pos();
        int oy = obj->get_y_pos();

        int dx = ox - sx;
        int dy = oy - sy;

        //check if object is infront and in range
        bool visible = false;
        if(direction == CarDirection::NORTH && dy >= 0 && abs(dx) <= range && dy <= range){
            visible = true;
        }
        if(direction == CarDirection::SOUTH && dy <= 0 && abs(dx) <= range && abs(dy) <= range){
            visible = true;
        }
        if(direction == CarDirection::EAST  && dx >= 0 && dx <= range && abs(dy) <= range){
            visible = true;
        }
        if(direction == CarDirection::WEST  && dx <= 0 && abs(dx) <= range && abs(dy) <= range){
            visible = true;
        }

        if(visible){      
            int distance = abs(dx) + abs(dy);

            if(canDetect(*obj, distance)){
                readings.push_back(createReading(*obj, distance));
            } 
        }

    }

    return readings;
}

bool CameraSensor::canDetect(const WorldObject&, int distance) const {
    return distance <= range;
}

SensorReading CameraSensor::createReading(const WorldObject& obj, int distance) const {
    SensorReading reading;
    reading.type = obj.getType();
    reading.position = obj.getPosition();
    reading.distance = distance;
    reading.objectID = obj.getID();
    reading.confidence = addNoise(accuracy * confidenceFromDistance(distance));

    //speed
    if(reading.type == ObjectType::MOVING_CAR){
        reading.speed = 2;
    }else if (reading.type == ObjectType::MOVING_BIKE){
        reading.speed = 1;
    }else{
        reading.speed = -1;
    }

    //direction
    if (auto* moving = dynamic_cast<const MovingObjects*>(&obj)){
        if(moving->get_direction() == "left"){
            reading.direction = Direction::WEST;
        }else if(moving->get_direction() == "right"){
            reading.direction = Direction::EAST;
        }else if(moving->get_direction() == "up"){
            reading.direction = Direction::NORTH;
        }else if(moving->get_direction() == "down"){
            reading.direction = Direction::SOUTH;
        }
    }else{
        reading.direction = Direction::UNKNOWN;
    }

    //traffic light color
    if(reading.type == ObjectType::TRAFFIC_LIGHT){
        string g = obj.GET_glyph();
        if(g == "R"){
            reading.trafficLight = TrafficLightColor::RED;
        }else if(g == "Y"){
            reading.trafficLight = TrafficLightColor::YELLOW;
        }else if(g == "G"){
            reading.trafficLight = TrafficLightColor::GREEN;
        }else{
            reading.trafficLight = TrafficLightColor::UNKNOWN;
        }
    }else{
        reading.trafficLight = TrafficLightColor::UNKNOWN;
    }

    //sign text
    if (reading.type == ObjectType::STOP_SIGN)
        reading.signText = "STOP";
    else{
        reading.signText = "N/A";
    }
    return reading;
}
