#include "../include/radarSensor.h"
#include "../include/MovingObjects.h"

using namespace std;

RadarSensor::RadarSensor() : Sensor(12, 0.95f) {}

vector<SensorReading> RadarSensor::scan(const GridWorld& world){
    vector<SensorReading> readings;

    auto objects = world.get_GridWorld();

    int sx = get<0>(position);
    int sy = get<1>(position);

    for(auto* obj : objects){
        ObjectType type = obj->getType();

        if(type == ObjectType::MOVING_CAR || type == ObjectType::MOVING_BIKE){

            int ox = obj->get_x_pos();
            int oy = obj->get_y_pos();

            int dx = ox - sx;
            int dy = oy - sy;

            //check if object is infront
            bool inFront = false;
            if (direction == CarDirection::NORTH && dy > 0 && dx == 0){
                inFront = true;
            }else if(direction == CarDirection::SOUTH && dy < 0 && dx == 0){
                 inFront = true;
            }else if(direction == CarDirection::EAST  && dx > 0 && dy == 0){
                inFront = true;
            }else if(direction == CarDirection::WEST  && dx < 0 && dy == 0){
                inFront = true;
            }

            if(inFront){
                int distance = abs(dx) + abs(dy);

                if(canDetect(*obj, distance)){
                    readings.push_back(createReading(*obj, distance));
                }
            } 
        }
    }
    return readings;
}

bool RadarSensor::canDetect(const WorldObject&, int distance) const{
    return distance <= range;
}

SensorReading RadarSensor::createReading(const WorldObject& obj, int distance) const{
    SensorReading reading;
    reading.type = obj.getType();
    reading.position = obj.getPosition();
    reading.distance = distance;
    reading.objectID = obj.getID();
    reading.confidence = addNoise(accuracy * confidenceFromDistance(distance));

    //speed
    if(reading.type == ObjectType::MOVING_CAR){
        reading.speed = 2;
    }else{
        reading.speed = 1;
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

    //radar doesn't know these
    reading.signText = "N/A";
    reading.trafficLight = TrafficLightColor::UNKNOWN;

    return reading;
}