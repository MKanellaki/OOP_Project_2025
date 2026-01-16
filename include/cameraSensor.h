#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include "sensor.h"

class CameraSensor : public Sensor {
protected:
    bool canDetect(const WorldObject& obj, int distance) const override;
    SensorReading createReading(const WorldObject& obj, int distance) const override;

public:
    CameraSensor();
    ~CameraSensor();

    std::vector<SensorReading> scan(const GridWorld& world) override;
};

#endif
