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
    GridWorld():dimX(40),dimY(40),simulationTicks(100),numMovingCars(3),numMovingBikes(4),
    numParkedCars(5),numStopSigns(2),numTraficLights(2),seed(time(NULL)){
    }; 
    int get_seed(){
        return seed;
    }; 
    void set_seed(int NEWseed){
        seed = NEWseed;
    };
    void set_dimX(int NEWdimX){
        dimX = NEWdimX;
    };
    void set_dimY(int NEWdimY){
        dimY = NEWdimY;
    };
    void set_simulationTicks(int NEWsimulationTicks){
        simulationTicks = NEWsimulationTicks;
    };
    int get_simulationTicks(){
        return simulationTicks;
    };
    void set_numMovingCars(int NEWnumMovingCars){
        numMovingCars = NEWnumMovingCars;
    };
    void set_numMovingBikes(int NEWnumMovingBikes){
        numMovingBikes = NEWnumMovingBikes;
    };
    void set_numMovingBikes(int NEWnumParkedCars){
        numParkedCars = NEWnumParkedCars;
    };
    void set_numStopSigns(int NEWnumStopSigns){
        numStopSigns = NEWnumStopSigns;
    };
    void set_numTraficLights(int NEWnumTraficLights){
        numTraficLights = NEWnumTraficLights;
    };
    void create_GridWorld(){
        srand(seed);
        for(int i=0 ; i<numMovingCars ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            MovingCar.push_back(new MovingCars());
            MovingCar[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numMovingBikes ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            MovingBike.push_back(new MovingBikes());
            MovingBike[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numParkedCars ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            StationaryVehicle.push_back(new StationaryVehicles());
            StationaryVehicle[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numStopSigns ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficSign.push_back(new TrafficSigns(true));
            TrafficSign[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numTraficLights ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficLight.push_back(new TrafficLights());
            TrafficLight[i]->add_pos(e1,e2);
        };
    };
    void first_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph){
        vector<WorldObject*> GridWorld[dimX][dimY];
        for(int i=0 ; i<numMovingCars ; i++){
            GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
        };
        for(int i=0 ; i<numParkedCars ; i++){
            GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
        };
        for(int i=0 ; i<numStopSigns ; i++){ 
            GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
        };
        for(int i=0 ; i<numTraficLights ; i++){
            GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
        };
        
        for(int y=0;y<dimY;y++){
            for(int x=0;x<dimX;x++){
                if(!((get<0>(Self_Driving_Car_pos)= dimX)&&(get<1>(Self_Driving_Car_pos)= dimY))){
                if(GridWorld[x][y].size()==0)cout <<'.';
                if(GridWorld[x][y].size()>=2)cout <<"(";
                for(int f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=2)cout<<")";
                };
                if(((get<0>(Self_Driving_Car_pos)= dimX)&&(get<1>(Self_Driving_Car_pos)= dimY))){
                if(GridWorld[x][y].size()>=1)cout <<"(";
                 cout <<Self_Driving_Car_glyph;
                for(int f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=1)cout<<")";
                };
            };
            cout <<endl;
        };
    };
    void NEW_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph){
        vector<WorldObject*> GridWorld[dimX][dimY];
        cout <<"\n"<<endl;
        cout <<"\n"<<endl;
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in()){
                MovingCar[i]->move();
                if(MovingCar[i]->get_x_pos()>=dimX){
                    MovingCar[i]->not_in();
                };
               if(MovingCar[i]->get_y_pos() >=dimY){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_x_pos()<0){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_y_pos() <0){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_in()){
                    GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
                };
            };
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in()){
                MovingBike[i]->move();
                if(MovingBike[i]->get_x_pos()>=dimX){
                    MovingBike[i]->not_in();;
                };
                if(MovingBike[i]->get_y_pos() >=dimY){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_x_pos()<0){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_y_pos() <0){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_in()){
                    GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
                };
            };
        };
    for(int i=0 ; i<numParkedCars ; i++){
        GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
    };
    for(int i=0 ; i<numStopSigns ; i++){ 
        GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
    };
    for(int i=0 ; i<numTraficLights ; i++){
        TrafficLight[i]->new_cycle();
        GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
    };
    for(int y=0;y<dimY;y++){
        for(int x=0;x<dimX;x++){
            if(!((get<0>(Self_Driving_Car_pos)= dimX)&&(get<1>(Self_Driving_Car_pos)= dimY))){
            if(GridWorld[x][y].size()==0)cout <<'.';
            if(GridWorld[x][y].size()>=2)cout <<"(";
            for(int f=0;f<GridWorld[x][y].size();f++){
                cout <<(GridWorld[x][y])[f]->GET_glyph();
            };
            if(GridWorld[x][y].size()>=2)cout<<")";
            };
            if(((get<0>(Self_Driving_Car_pos)= dimX)&&(get<1>(Self_Driving_Car_pos)= dimY))){
            if(GridWorld[x][y].size()>=1)cout <<"(";
            cout <<Self_Driving_Car_glyph;
            for(int f=0;f<GridWorld[x][y].size();f++){
                cout <<(GridWorld[x][y])[f]->GET_glyph();
            };
            if(GridWorld[x][y].size()>=1)cout<<")";
            };
        };
        cout <<endl;
    };
    };
};
#endif