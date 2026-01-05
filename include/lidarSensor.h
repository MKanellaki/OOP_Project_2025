#ifndef LIDARSENSOR_H
#define LIDARSENSOR_H

#include "Sensor.h"

class LidarSensor : public Sensor{
    protected:
        bool canDetect(const WorldObject& obj, int distance) const override;
        SensorReading createReading(const WorldObject& object, int distance) const override;
    public:
        LidarSensor();
        ~LidarSensor();

        std::vector<SensorReading> scan(const GridWorld& world) override;
};

#endif