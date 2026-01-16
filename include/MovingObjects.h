#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H
#include "WorldObject.h"
class MovingObjects : public WorldObject{
protected:
string direction;
int speed;
bool in;
public:
bool get_in(){
        return in;
    };
    void not_in(){
        in= false;
    };
string get_direction(){
        return direction;
    };
    void move(){
        int x=get_x_pos();
        int y=get_y_pos();
        if (direction=="left")x=x+speed;
        if (direction=="right")x=x-speed;
        if (direction=="up")y=y+speed;
        if (direction=="down")y=y-speed;
        add_pos(x,y);
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
    };
}; 
#endif