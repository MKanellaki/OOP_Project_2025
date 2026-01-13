#include "include/simulation.h"
#include "include/GridWorld.h"
#include "src/GridWorld.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int main(){
GridWorld World;
World.set_dimY(10);
World.set_dimX(10);
World.set_simulationTicks(10);
World.create_GridWorld();
World.first_tick(make_tuple(0,0),"@");
for(int i=1;i<10;i++)World.NEW_tick(make_tuple(i,i),"@");
};
