#ifndef TRAFFICSIGNS_H
#define TRAFFICSIGNS_H
#include "StaticObjects.h"
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
#endif