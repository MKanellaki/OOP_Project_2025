#ifndef SENSOR_H
#define SENSOR_H

#include <tuple>
#include <string>
#include <vector>
#include "sensorReading.h"
#include "GridWorld.h"
#include "WorldObject.h"
#include "selfDrivingCar.h"

class Sensor{
    protected:
        int range;
        std::tuple<int, int> position;
        float accuracy;
        CarDirection direction;

        float confidenceFromDistance(int distance) const;
        float addNoise(float confidence) const;

        virtual bool canDetect(const WorldObject& obj, int distance) const = 0;
        virtual SensorReading createReading(const WorldObject& obj, int distance) const = 0;
    public:
        Sensor(int r, float acc);
        virtual ~Sensor();

        virtual std::vector<SensorReading> scan(const GridWorld& world) = 0;

        void updatePosition(int x, int y);
        void updateDirection(CarDirection dir);
        
};

#endif