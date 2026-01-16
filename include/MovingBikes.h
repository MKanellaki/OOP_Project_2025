#ifndef MOVINGBIKES_H
#define MOVINGBIKES_H
#include "MovingObjects.h"
class MovingBikes : public MovingObjects{
    protected:
    static int MovingBikescount;
    public:
MovingBikes(){
        MovingBikescount++;//counts the objects that exist of tha type
        in =true;//sets everything with the necessary variables
        glyph="B";
        ID.ID_string="MovingBike:";
        Type=ObjectType::MOVING_BIKE;
        ID.ID_int=MovingBikescount;
        speed=1;
        int f =rand()%(4);//gets a random number and puts a direction based on it
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
#endif