#ifndef SIMULATION_H
#define SIMULATION_H
#include "sensorReading.h"
#include <tuple>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class ID_class{
    public:
   string ID_string;
   int ID_int; 
};
class WorldObject{
protected:
ID_class ID;
string glyph;
int X;//οριζόντιος άξονας 
int Y;//κάθ ετος άξονας
ObjectType Type;
public:
string GET_glyph(){
   return glyph;
};
virtual void describe(){};
void add_pos(int x,int y){
    X=x;
    Y=y;
};
int get_x_pos(){
    return X;
};
int get_y_pos(){
    return Y;
};
string getID(){
    return ID.ID_string;
};
tuple<int, int> getPosition(){
    return make_tuple(X,Y);
};
ObjectType getType(){
return Type;
};
};
class MovingObjects : public WorldObject{
protected:
string direction;
int speed;
bool in;
public:
bool get_in(){
        return in;
    };
    void not_in(){
        in= false;
    };
string get_direction(){
        return direction;
    };
    void move(){
        int x=get_x_pos();
        int y=get_y_pos();
        if (direction=="left")x=x+speed;
        if (direction=="right")x=x-speed;
        if (direction=="up")y=y+speed;
        if (direction=="down")y=y-speed;
        add_pos(x,y);
    };
}; 
class MovingCars : public MovingObjects{
    protected:
    static int MovingCarscount;
    public:
    MovingCars(){
        MovingCarscount++;
        in =true;
        glyph ="C";
        ID.ID_string="MovingCar:";
        Type=ObjectType::MOVING_CAR ;
        ID.ID_int=MovingCarscount;
        speed=2;
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
      //  cout <<direction <<"\n"<<endl;
    };
    void describe()override{
       cout <<"MovingCars direction\n"<<endl;
       cout <<direction <<"\n"<<endl;
    };
};
int MovingCars::MovingCarscount=0;
class MovingBikes : public MovingObjects{
    protected:
    static int MovingBikescount;
    public:
MovingBikes(){
        MovingBikescount++;
        in =true;
        glyph="B";
        ID.ID_string="MovingBike:";
        Type=ObjectType::MOVING_BIKE;
        ID.ID_int=MovingBikescount;
        speed=1;
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
    };
    void describe()override{
       cout <<"MovingBikes direction\n"<<endl;
       cout <<direction <<"\n"<<endl;
    };
};
int MovingBikes::MovingBikescount=0;
class StaticObjects : public WorldObject{
};
class StationaryVehicles : public StaticObjects{
protected:
    static int ParkedCarcount;
public:
    StationaryVehicles(){
        ParkedCarcount++;
        glyph="P";
        ID.ID_string="ParkedCar:";
        Type=ObjectType::PARKED_CAR;
        ID.ID_int=ParkedCarcount;
    };
void describe()override{
       cout <<"StationaryVehicles \n"<<endl;
    };
};
int StationaryVehicles::ParkedCarcount=0;
class TrafficSigns : public StaticObjects{
protected:
bool is_STOP;
static int TrafficSignsSTOPcount;
public:
TrafficSigns(bool STOP):is_STOP(STOP){
    TrafficSignsSTOPcount++;
    glyph="S";
    ID.ID_string="TrafficSignStop:";
    Type=ObjectType::STOP_SIGN;
    ID.ID_int=TrafficSignsSTOPcount;
};
void describe()override{
       cout <<"TrafficSigns \n"<<endl;
       if(is_STOP)cout <<"STOP \n"<<endl;
       if(!is_STOP)cout <<"NOT STOP \n"<<endl;
    };
};
int TrafficSigns::TrafficSignsSTOPcount=0;
class TrafficLights : public StaticObjects{
protected:
static int TrafficLightscount;
int ticks;
public:
TrafficLights():ticks(1){
    TrafficLightscount++;
    glyph="R";
    ID.ID_string="TrafficLights:";
    Type=ObjectType::TRAFFIC_LIGHT;
    ID.ID_int=TrafficLightscount;
};
void new_cycle(){
    ticks++;
    if((glyph=="R")&&(ticks>4)){
        glyph="G";
        ticks=1;
    };
    if((glyph=="G")&&(ticks>8)){
        glyph="Y";
        ticks=1;
    };
    if((glyph=="Y")&&(ticks>2)){
        glyph="R";
        ticks=0;
    };
};
void describe()override{
       cout <<"TrafficLights \n"<<endl;
       if(glyph=="R")cout <<"RED \n"<<endl;
       if(glyph=="Y")cout <<"YELLOW \n"<<endl;
       if(glyph=="G")cout <<"GREEN \n"<<endl;
    };
};
int TrafficLights::TrafficLightscount=0;
#endif