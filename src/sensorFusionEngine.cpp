#include "../include/sensorFusionEngine.h"

using namespace std;

SensorFusionEngine::SensorFusionEngine(float minConf) : minConfidenceThreshold(minConf){}

vector<SensorReading> SensorFusionEngine::fuseSensorData(const vector<SensorReading>& allReadings){
    unordered_map<string, vector<SensorReading>> grouped;

    for(const SensorReading& r : allReadings){
        grouped[r.objectID].push_back(r);
    }

    vector<SensorReading> fusedResults;

    for(auto& [id, readings] : grouped){
        float confidenceSum = 0.0f;
        float weightedDistance = 0.0f;

        SensorReading fused = readings[0]; // base object
        bool seenBike = false;

        for(const SensorReading& r : readings){
            confidenceSum += r.confidence;
            weightedDistance += r.distance * r.confidence;

            if(r.type == ObjectType::MOVING_BIKE){
                seenBike = true;
            }
            // Prefer richer data
            if(r.speed != -1){
                fused.speed = r.speed;
            }
            if(r.direction != Direction::UNKNOWN){
                fused.direction = r.direction;
            }
            if(r.signText != "N/A"){
                fused.signText = r.signText;
            }
            if(r.trafficLight != TrafficLightColor::UNKNOWN){
                fused.trafficLight = r.trafficLight;
            }
        }

        if(confidenceSum > 0.0f){
            fused.distance = static_cast<int>(weightedDistance / confidenceSum);
            fused.confidence = confidenceSum / readings.size();
        }

        if(fused.confidence >= minConfidenceThreshold || seenBike){
            fusedResults.push_back(fused);
        }
    }

    return fusedResults;
}