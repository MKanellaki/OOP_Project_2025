#ifndef SENSORFUSIONENGINE_H
#define SENSORFUSIONENGINE_H

#include <vector>
#include <unordered_map>
#include <string>

#include "sensorReading.h"

class SensorFusionEngine{
    private:
        float minConfidenceThreshold;
    public:
        SensorFusionEngine(float minConf = 0.4f);

        std::vector<SensorReading> fuseSensorData(const std::vector<SensorReading>& allReadings);
};

#endif