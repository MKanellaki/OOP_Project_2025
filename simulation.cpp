#include "include/GridWorld.h"
#include "src/GridWorld.cpp"
using namespace std;
int main(){
GridWorld World;
World.set_dimY(10);
World.set_dimX(10);
World.set_simulationTicks(10);
World.create_GridWorld();
World.visualization_full(make_tuple(0,0),"@");
for(int i=1;i<10;i++){
    World.NEW_tick();
World.visualization_pov(make_tuple(i,i),"@",5);
};
World.visualization_full(make_tuple(9,9),"@");
};
