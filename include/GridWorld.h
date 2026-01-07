#ifndef GRIDWORLD_H
#define GRIDWORLD_H
#include "simulation.h"
#include "sensorReading.h"
#include <tuple>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class GridWorld{
protected:
    int dimX ;
    int dimY ; 
    int simulationTicks;
    int numMovingCars ;
    int numMovingBikes ;
    int numParkedCars ;
    int numStopSigns ;
    int numTraficLights ;
    int seed;
    vector<MovingCars*> MovingCar;
    vector<MovingBikes*> MovingBike;
    vector<StationaryVehicles*> StationaryVehicle;
    vector<TrafficSigns*> TrafficSign;
    vector<TrafficLights*> TrafficLight;
public:
    GridWorld():dimX(40),dimY(40),simulationTicks(100),numMovingCars(3),numMovingBikes(4),numParkedCars(5),
        numStopSigns(2),numTraficLights(2),seed(time(NULL)){
    }; 
    int get_seed(){
        return seed;
    }; 
    int set_seed(int NEWseed){
        seed = NEWseed;
    };
};
#endif