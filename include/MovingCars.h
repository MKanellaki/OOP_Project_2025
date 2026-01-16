#ifndef MOVINGCARS_H
#define MOVINGCARS_H
#include "MovingObjects.h"
class MovingCars : public MovingObjects{
    protected:
    static int MovingCarscount;
    public:
    MovingCars(){
        MovingCarscount++;//counts the objects that exist of tha type
        in =true;//sets everything with the default variables
        glyph ="C";
        ID.ID_string="MovingCar:";
        Type=ObjectType::MOVING_CAR ;
        ID.ID_int=MovingCarscount;
        speed=2;
        int f =rand()%(4);//gets a random number and puts a direction based on it
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
    };
    void describe()override{
       cout <<"MovingCars direction\n"<<endl;
       cout <<direction <<"\n"<<endl;
    };
};
#endif