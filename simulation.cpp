#include "include/simulation.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int main(){
    srand(time(NULL));
//    40×40
int dimX = 40;
int dimY = 20;
vector<WorldObject*> GridWorld[dimX][dimY];  
int simulationTicks= 5;
int numMovingCars = 3 ;
int numMovingBikes = 4 ;
int numParkedCars = 5 ;
int numStopSigns = 2;
int numTraficLights = 2 ;
vector<MovingCars*> MovingCar;
vector<MovingBikes*> MovingBike;
vector<StationaryVehicles*> StationaryVehicle;
vector<TrafficSigns*> TrafficSign;
vector<TrafficLights*> TrafficLight;
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
if(GridWorld[x][y].size()==0)cout <<'_';
if(GridWorld[x][y].size()>=2)cout <<"(";
for(int f=0;f<GridWorld[x][y].size();f++){
cout <<(GridWorld[x][y])[f]->GET_glyph();
};
if(GridWorld[x][y].size()>=2)cout<<")";
};
//cout <<"\n"<<endl;
cout <<endl;
};
int size1;
for(int Ticks=1 ; Ticks<simulationTicks ; Ticks++){
 
for(int x=0;x<dimX;x++){
for(int y=0;y<dimY;y++){
size1 = GridWorld[x][y].size();
//for(int f=0;f<GridWorld[x][y].size();f++){
//GridWorld[x][y].pop_back();
GridWorld[x][y].clear();
//};
};
};
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
///*
for(int y=0;y<dimY;y++){
for(int x=0;x<dimX;x++){
if(GridWorld[x][y].size()==0)cout <<'.';
if(GridWorld[x][y].size()>=2)cout <<"(";
for(int f=0;f<GridWorld[x][y].size();f++){
cout <<(GridWorld[x][y])[f]->GET_glyph();
};
if(GridWorld[x][y].size()>=2)cout<<")";
};
cout <<endl;
};
};
};