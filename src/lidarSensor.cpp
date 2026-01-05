#include "LidarSensor.h"
using namespace std;

LidarSensor::LidarSensor():Sensor(9, 0.99f){} 

vector<SensorReading> LidarSensor::scan(const GridWorld& world) const{
    vector<SensorReading> readings;


}

bool LidarSensor::canDetect(const WorldObject&, int distance) const{
    //lidar detects everything in range
    return true;
}

SensorReading LidarSensor::createReading(const WorldObject& obj, int distance) const{
    SensorReading reading;
    //fill correct worldObject functions
    reading.type = obj.getType();
    reading.position = obj.getPosition();
    reading.distance = distance;
    reading.objectID = obj.getID();
    reading.confidence = addNoise(confidenceFromDistance(distance));

    //lidar doesn't know these
    reading.speed = -1;
    reading.direction = "N/A";
    reading.signText = "N/A";
    reading.trafficLight = TrafficLightColor::UNKNOWN;

    return reading;
}