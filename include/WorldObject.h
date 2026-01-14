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
   string ID_string;
   int ID_int; 
};
class WorldObject{
protected:
ID_class ID;
string glyph;
int X;//οριζόντιος άξονας 
int Y;//κάθ ετος άξονας
ObjectType Type;
public:
string GET_glyph(){
   return glyph;
};
virtual void describe(){};
void add_pos(int x,int y){
    X=x;
    Y=y;
};
int get_x_pos(){
    return X;
};
int get_y_pos(){
    return Y;
};
string getID(){
    return ID.ID_string;
};
tuple<int, int> getPosition(){
    return make_tuple(X,Y);
};
ObjectType getType(){
return Type;
};
};
#endif