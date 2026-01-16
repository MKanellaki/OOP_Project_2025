#ifndef STATIONARYVEHICLES_H
#define STATIONARYVEHICLES_H
#include "StaticObjects.h"
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
#endif