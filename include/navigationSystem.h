#ifndef NAVIGATIONSYSTEM_H
#define NAVIGATIONSYSTEM_H

#include <vector>
#include <tuple>

#include "sensorFusionEngine.h"
#include "sensorReading.h"
#include "selfDrivingCar.h"

class NavigationSystem{
private:
    SensorFusionEngine fusion;
    std::vector<std::tuple<int,int>> gpsTargets;//multiple targets?
    size_t currentTargetIndex;

    std::vector<SensorReading> fusedWorld;

    bool isAhead(const SelfDrivingCar& car, const SensorReading& r) const;

public:
    NavigationSystem(float minConfidence = 0.4f);

    void setGPSTargets(const std::vector<std::tuple<int,int>>& targets);

    void updateSensorData(const std::vector<SensorReading>& rawReadings);

    void makeDecision(SelfDrivingCar& car);
};

#endif
