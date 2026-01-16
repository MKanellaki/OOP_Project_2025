#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H
#include "StaticObjects.h"
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
#endif