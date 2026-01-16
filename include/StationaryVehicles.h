#ifndef STATIONARYVEHICLES_H
#define STATIONARYVEHICLES_H
#include "StaticObjects.h"
class StationaryVehicles : public StaticObjects{
protected:
    static int ParkedCarcount;
public:
    StationaryVehicles(){
        ParkedCarcount++;//counts the objects that exist of tha type
        glyph="P";//sets everything with the necessary variables
        ID.ID_string="ParkedCar:";
        Type=ObjectType::PARKED_CAR;
        ID.ID_int=ParkedCarcount;
    };
void describe()override{
       cout <<"StationaryVehicles \n"<<endl;
    };
};
#endif