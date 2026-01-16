#ifndef MOVINGOBJECTS_H
#define MOVINGOBJECTS_H
#include "WorldObject.h"
class MovingObjects : public WorldObject{
protected:
string direction;
int speed;
bool in;//to see if it's in
public:
bool get_in(){//Every get_.... return the corresponding variable
        return in;
    };
    void not_in(){
        in= false;
    };
string get_direction() const{
        return direction;
    };
    void move(){//based on the direction changing the x or y by the speed  to "move"
        int x=get_x_pos();
        int y=get_y_pos();
        if (direction=="left")x=x-speed;
        if (direction=="right")x=x+speed;
        if (direction=="up")y=y+speed;
        if (direction=="down")y=y-speed;
        add_pos(x,y);//updates the position using  x and y
        int f =rand()%(4);//gets a random number and changes the direction based on it
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
    };
}; 
#endif