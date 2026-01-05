#ifndef SENSOR_H
#define SENSOR_H

#include <tuple>
#include <string>
#include <vector>
#include "SensorReading.h"

class Sensor{
    protected:
        int range;
        sdt::tuple<int, int> position;
        Direction direction;
        float accuracy;

        virtual bool canDetect(const WorldObject& obj, int distance) const = 0;
        virtual SensorReading createReading(const WorldObject& obj, int distance) const = 0;
    public:
        Sensor(int range, float accuracy);
        virtual ~Sensor();

        virtual std::vector<SensorReading> scan(const GridWorld& world) = 0;

        void updatePosition(int x, int y);
        void updateDirection(const string& dir);
        

};

#endif