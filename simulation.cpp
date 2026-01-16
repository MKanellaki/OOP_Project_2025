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
    srand(World.get_seed());
for(int i=1;i<10;i++){
    World.NEW_tick();

      int f =rand()%(4);
        if (f==0)World.visualization_pov_front(make_tuple(i,i),"@",Direction::NORTH);
        if (f==1)World.visualization_pov_front(make_tuple(i,i),"@",Direction::EAST);
        if (f==2)World.visualization_pov_front(make_tuple(i,i),"@",Direction::WEST);
        if (f==3)World.visualization_pov_front(make_tuple(i,i),"@",Direction::SOUTH);
};
World.visualization_full(make_tuple(9,9),"@");
};
