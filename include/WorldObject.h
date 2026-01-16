#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "sensorReading.h"
#include <tuple>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class ID_class{
    public:
   string ID_string;//the name of the category
   int ID_int; //serial number per category
};
class WorldObject{
protected:
ID_class ID;
string glyph;
int X;//οριζόντιος άξονας 
int Y;//κάθ ετος άξονας
ObjectType Type;
public:
string GET_glyph() const{//Every get_.... return the corresponding variable
   return glyph;
};
virtual void describe(){};
void add_pos(int x,int y){//adds position
    X=x;
    Y=y;
};
int get_x_pos() const{
    return X;
};
int get_y_pos() const{
    return Y;
};
string getID() const{
    return ID.ID_string;
};
tuple<int, int> getPosition() const{
    return make_tuple(X,Y);
};
ObjectType getType() const{
return Type;
};
};
#endif