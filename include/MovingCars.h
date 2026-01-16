#ifndef MOVINGCARS_H
#define MOVINGCARS_H
#include "MovingObjects.h"
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
#endif