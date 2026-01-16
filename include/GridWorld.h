#ifndef GRIDWORLD_H
#define GRIDWORLD_H
#include "selfDrivingCar.h"
#include "TrafficLights.h"
#include "StationaryVehicles.h"
#include "TrafficSigns.h"
#include "MovingBikes.h"
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
    numParkedCars(5),numStopSigns(2),numSigns(2),numTraficLights(2),seed(time(NULL)){};
    // It setups the variables with the default ones
    int get_seed()const; //Every get_.... return the corresponding variable
    void set_seed(int NEWseed);//Every set_.... changes the corresponding variable
    void set_dimX(int NEWdimX);
    void set_dimY(int NEWdimY);
    void set_simulationTicks(int NEWsimulationTicks);
    int get_simulationTicks() const;
    void set_numMovingCars(int NEWnumMovingCars);
    void set_numMovingBikes(int NEWnumMovingBikes);
    void set_numParkedCars(int NEWnumParkedCars);
    void set_numStopSigns(int NEWnumStopSigns);
    void set_numSigns(int NEWnumSigns);
    void set_numTraficLights(int NEWnumTraficLights);
    void create_GridWorld();//must be called after the sets (if used) and before the
    // (visualization_full,visualization_pov,NEW_tick,get_GridWorld) so that it can set up everything
    void visualization_full(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph);
    //prints the complete world in a grid
    void visualization_pov(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph,int radius);
    //prints the world around the vehicle based on the radius
    void visualization_pov_front(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph,Direction direction);
    void NEW_tick();
    //it’s called for every tick to update the objects
    vector<WorldObject*> get_GridWorld()const;
    //it returns a vector with all the Objects
    ~GridWorld();
};

#endif