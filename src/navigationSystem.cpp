#include "../include/navigationSystem.h"
#include <cmath>

using namespace std;

NavigationSystem::NavigationSystem(float minConfidence) : fusion(minConfidence), currentTargetIndex(0){}

void NavigationSystem::setGPSTargets(const vector<tuple<int,int>>& targets){
    gpsTargets = targets;
    currentTargetIndex = 0;
}

void NavigationSystem::updateSensorData(const vector<SensorReading>& rawReadings){
    fusedWorld = fusion.fuseSensorData(rawReadings);
}

bool NavigationSystem::isAhead(const SelfDrivingCar& car, const SensorReading& r) const{
    auto [cx, cy] = car.get_position();
    auto [ox, oy] = r.position;

    switch(car.get_direction()){
        case CarDirection::NORTH:
            return oy > cy && ox == cx;
        case CarDirection::SOUTH:
            return oy < cy && ox == cx;
        case CarDirection::EAST:
            return ox > cx && oy == cy;
        case CarDirection::WEST:
            return ox < cx && oy == cy;
    }
    return false;
}

void NavigationSystem::makeDecision(SelfDrivingCar& car) {
    if (currentTargetIndex >= gpsTargets.size())
        return; // no more targets

    auto [cx, cy] = car.get_position();
    auto [tx, ty] = gpsTargets[currentTargetIndex];

    int distanceToTarget = abs(tx - cx) + abs(ty - cy);

    // 1. Check world hazards
    for (const auto& r : fusedWorld) {
        if (!isAhead(car, r))
            continue;

        // STOP conditions
        if ((r.type == ObjectType::TRAFFIC_LIGHT &&
             (r.trafficLight == TrafficLightColor::RED ||
              r.trafficLight == TrafficLightColor::YELLOW)) &&
            r.distance <= 3) {
            car.set_speed(SpeedState::STOPPED);
            return;
        }

        if (r.type == ObjectType::STOP_SIGN && r.distance <= 3) {
            car.set_speed(SpeedState::STOPPED);
            return;
        }

        // Slow down for obstacles
        if ((r.type == ObjectType::MOVING_CAR ||
             r.type == ObjectType::MOVING_BIKE) &&
            r.distance <= 2) {
            car.decelerate();
            return;
        }
    }

    // 2. GPS proximity slowing
    if (distanceToTarget <= 5) {
        car.decelerate();
    } else {
        car.accelerate();
    }

    // 3. Direction toward target
    if (cx != tx) {
        car.set_direction((tx > cx) ? CarDirection::EAST : CarDirection::WEST);
    } else if (cy != ty) {
        car.set_direction((ty > cy) ? CarDirection::NORTH : CarDirection::SOUTH);
    } else {
        // Arrived at target
        currentTargetIndex++;
    }
}