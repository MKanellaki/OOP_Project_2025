#ifndef MOVINGBIKRS_H
#define MOVINGBIKES_H
#include "MovingObjects.h"
class MovingBikes : public MovingObjects{
    protected:
    static int MovingBikescount;
    public:
MovingBikes(){
        MovingBikescount++;
        in =true;
        glyph="B";
        ID.ID_string="MovingBike:";
        Type=ObjectType::MOVING_BIKE;
        ID.ID_int=MovingBikescount;
        speed=1;
        int f =rand()%(4);
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
int MovingBikes::MovingBikescount=0;
#endif