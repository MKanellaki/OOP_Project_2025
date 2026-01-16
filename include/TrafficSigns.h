#ifndef TRAFFICSIGNS_H
#define TRAFFICSIGNS_H
#include "StaticObjects.h"
class TrafficSigns : public StaticObjects{
protected:
bool is_STOP;
static int TrafficSignsSTOPcount;
static int TrafficSignscount;
string writtenSigns;
public:
TrafficSigns(bool STOP):is_STOP(STOP){
    if(is_STOP){//checks if it is (stop) or not
    TrafficSignsSTOPcount++;//counts the objects that exist of tha type (stop)
    glyph="S";//sets everything with the necessary variables
    ID.ID_string="TrafficSignStop:";
    Type=ObjectType::STOP_SIGN;
    ID.ID_int=TrafficSignsSTOPcount;
    writtenSigns="STOP";
};
    if(!is_STOP){//checks if it is (stop) or not
    TrafficSignscount++;//counts the objects that exist of tha type (not stop)
    glyph="?";//sets everything with the necessary variables
    ID.ID_string="TrafficSign:";
    Type=ObjectType::SIGN;
    ID.ID_int=TrafficSignscount;
    int f =rand()%(4);//gets a random number and puts a message based on it
        if (f==0)writtenSigns="ΕΚΠΑ";
        if (f==1)writtenSigns="ΑΘΗΝΑ";
        if (f==2)writtenSigns="ΜΕΣΗ ΤΟΥ ΠΟΥΘΕΝΑ";
        if (f==3)writtenSigns="ΧΑΘΗΚΕΣ!!!!";
};
};
void describe()override{
       cout <<"TrafficSigns \n"<<endl;
       if(is_STOP)cout <<"STOP \n"<<endl;
       if(!is_STOP)cout <<"NOT STOP \n"<<endl;
    };
};
#endif