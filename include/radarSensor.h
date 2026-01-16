#ifndef RADARSENSOR_H
#define RADARSENSOR_H

#include "sensor.h"

class RadarSensor : public Sensor{
    protected:
        bool canDetect(const WorldObject& obj, int distance) const override;
        SensorReading createReading(const WorldObject& object, int distance) const override;
    public:
        RadarSensor();
        ~RadarSensor();

        std::vector<SensorReading> scan(const GridWorld& world) override;
};

#endif