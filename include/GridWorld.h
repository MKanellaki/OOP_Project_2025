#ifndef GRIDWORLD_H
#define GRIDWORLD_H
#include "TrafficLights.h"
#include "StationaryVehicles.h"
#include "TrafficSigns.h"
#include "MovingBikes.h"
#include "MovingCars.h"
#include "MovingCars.h"
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
    int numSigns;
    int numTraficLights ;
    int seed;
    vector<MovingCars*> MovingCar;
    vector<MovingBikes*> MovingBike;
    vector<StationaryVehicles*> StationaryVehicle;
    vector<TrafficSigns*> TrafficSign;
    vector<TrafficLights*> TrafficLight;
public:
    GridWorld():dimX(40),dimY(40),simulationTicks(100),numMovingCars(3),numMovingBikes(4),
    numParkedCars(5),numStopSigns(2),numSigns(2),numTraficLights(2),seed(time(NULL)){
    }; 
    int get_seed(); 
    void set_seed(int NEWseed);
    void set_dimX(int NEWdimX);
    void set_dimY(int NEWdimY);
    void set_simulationTicks(int NEWsimulationTicks);
    int get_simulationTicks();
    void set_numMovingCars(int NEWnumMovingCars);
    void set_numMovingBikes(int NEWnumMovingBikes);
    void set_numParkedCars(int NEWnumParkedCars);
    void set_numStopSigns(int NEWnumStopSigns);
    void set_numSigns(int NEWnumSigns);
    void set_numTraficLights(int NEWnumTraficLights);
    void create_GridWorld();
    void first_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph);
    void NEW_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph);
    vector<WorldObject*> get_GridWorld();
    ~GridWorld();
};

#endif