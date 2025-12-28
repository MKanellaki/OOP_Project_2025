#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

class WorldObject{
protected:
string ID;
string glyph;
public:
virtual void describe(){};
};
class MovingObjects : public WorldObject{
protected:
string direction;
int speed;
public:

string get_direction(){
        return direction;
    };
}; 
class MovingCars : public MovingObjects{
    public:
    MovingCars(){
        speed=2;
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
        cout <<direction <<"\n"<<endl;
    };
    void describe()override{
       cout <<"direction\n"<<endl;
       cout <<direction <<"\n"<<endl;
    };
};
class MovingBikes : public MovingObjects{
    public:
MovingBikes(){
        speed=1;
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
    };
};
class StaticObjects : public WorldObject{

};
class TrafficSigns : public StaticObjects{
protected:
bool is_STOP;
public:
TrafficSigns(bool STOP):is_STOP(STOP){};
};
class STOP : public TrafficSigns{

};
class TrafficLights : public StaticObjects{
protected:
bool RED;
bool YELLOW;
bool GREEN;
int ticksRED;
int ticksYELLOW;
int ticksGREEN;
public:
TrafficLights():RED(true),YELLOW(false),GREEN(false),ticksRED(1),ticksYELLOW(0),ticksGREEN(0){};
void new_cycle(){
    if(RED)ticksRED++;
    if(YELLOW)ticksYELLOW++;
    if(GREEN)ticksGREEN++;
    if(ticksRED>4){
        GREEN=true;
        YELLOW=false;
        RED=false;
        ticksGREEN=1;
        ticksRED=0;
        ticksYELLOW=0;
    };
    if(ticksGREEN>8){
        YELLOW=true;
        GREEN=false;
        RED=false;
        ticksGREEN=0;
        ticksRED=0;
        ticksYELLOW=1;
    };
    if(ticksYELLOW>2){
        RED=true;
        GREEN=false;
        YELLOW=false;
        ticksGREEN=0;
        ticksRED=1;
        ticksYELLOW=0;
    };
};
};
int main(){
    srand(time(NULL));
//    40×40
WorldObject* GridWorld[40][40];  

int numMovingCars = 3 ;
int numMovingBikes = 4 ;
int numParkedCars = 5 ;
int numStopSigns = 2;
int numTraficLights = 2 ;
 
 
for(int i=0 ; i<numMovingCars ; i++){   
int e1 =rand()%(40);
int e2 =rand()%(40);
GridWorld[e1][e2] = new MovingCars();
};
for(int i=0 ; i<40 ; i++){   
for(int e=0 ; e<40 ; e++){   
GridWorld[i][e]->describe();//not finish error
};
};
};