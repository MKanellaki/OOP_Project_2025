#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H
#include "StaticObjects.h"
class TrafficLights : public StaticObjects{
protected:
static int TrafficLightscount;
int ticks;
public:
TrafficLights():ticks(1){
    TrafficLightscount++;//counts the objects that exist of tha type
    glyph="R";//sets everything with the necessary variables
    ID.ID_string="TrafficLights:";
    Type=ObjectType::TRAFFIC_LIGHT;
    ID.ID_int=TrafficLightscount;
};
void new_cycle(){
    ticks++;//increases ticks
    if((glyph=="R")&&(ticks>4)){//updates the color based on the ticks and the next color
        glyph="G";
        ticks=1;
    };
    if((glyph=="G")&&(ticks>8)){
        glyph="Y";
        ticks=1;
    };
    if((glyph=="Y")&&(ticks>2)){
        glyph="R";
        ticks=1;
    };
};
void describe()override{
       cout <<"TrafficLights \n"<<endl;
       if(glyph=="R")cout <<"RED \n"<<endl;
       if(glyph=="Y")cout <<"YELLOW \n"<<endl;
       if(glyph=="G")cout <<"GREEN \n"<<endl;
    };
};
#endif