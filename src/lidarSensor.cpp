#include "../include/lidarSensor.h"
using namespace std;

LidarSensor::LidarSensor():Sensor(9, 0.99f){} 

vector<SensorReading> LidarSensor::scan(const GridWorld& world){
    vector<SensorReading> readings;

    auto objects = world.get_GridWorld();

    int sx = get<0>(position);
    int sy = get<1>(position);

    for(auto* obj : objects){
        int ox = obj->get_x_pos();
        int oy = obj->get_y_pos();

        int distance = abs(ox - sx) + abs(oy - sy);

        if(canDetect(*obj, distance)){
            readings.push_back(createReading(*obj, distance));
        } 
    }

    return readings;

}

bool LidarSensor::canDetect(const WorldObject&, int distance) const{
    return distance <= range;
}

SensorReading LidarSensor::createReading(const WorldObject& obj, int distance) const{
    SensorReading reading;
    reading.type = obj.getType();
    reading.position = obj.getPosition();
    reading.distance = distance;
    reading.objectID = obj.getID();
    reading.confidence = addNoise(confidenceFromDistance(distance));

    //lidar doesn't know these
    reading.speed = -1;
    reading.direction = Direction::UNKNOWN;
    reading.signText = "N/A";
    reading.trafficLight = TrafficLightColor::UNKNOWN;

    return reading;
}