#include "../include/GridWorld.h"
    int apolito(int x){//returns the absolute value of the character
        if(x<0)return -x;
        return x;
    };
    int GridWorld::get_seed()const{//Every get_.... return the corresponding variable
        return seed;
    }; 
    void GridWorld::set_seed(int NEWseed){//Every set_.... changes the corresponding variable
        seed = NEWseed;
    };
    void GridWorld::set_dimX(int NEWdimX){
        dimX = NEWdimX;
    };
    void GridWorld::set_dimY(int NEWdimY){
        dimY = NEWdimY;
    };
    void GridWorld::set_simulationTicks(int NEWsimulationTicks){
        simulationTicks = NEWsimulationTicks;
    };
    int GridWorld::get_simulationTicks()const{
        return simulationTicks;
    };
    void GridWorld::set_numMovingCars(int NEWnumMovingCars){
        numMovingCars = NEWnumMovingCars;
    };
    void GridWorld::set_numMovingBikes(int NEWnumMovingBikes){
        numMovingBikes = NEWnumMovingBikes;
    };
    void GridWorld::set_numParkedCars(int NEWnumParkedCars){
        numParkedCars = NEWnumParkedCars;
    };
    void GridWorld::set_numStopSigns(int NEWnumStopSigns){
        numStopSigns = NEWnumStopSigns;
    };
    void GridWorld::set_numSigns(int NEWnumSigns){
        numSigns = NEWnumSigns;
    };
    void GridWorld::set_numTraficLights(int NEWnumTraficLights){
        numTraficLights = NEWnumTraficLights;
    };
void GridWorld::create_GridWorld(){//must be called after the sets (if used) and before the
    // (visualization_full,visualization_pov,NEW_tick,get_GridWorld) so that it can set up everything
        srand(seed);
        for(int i=0 ; i<numMovingCars ; i++){   
            int e1 =rand()%(dimX);//Based on srand and its seed, rand creates a random number 
            //and then using (%(dimX)) divides it by dimX and keeps the remainder, and so it 
            //ends up having a random number starting from 0 to dimX.
            int e2 =rand()%(dimY);//Based on srand and its seed, rand creates a random number 
            //and then using (%(dimY)) divides it by dimY and keeps the remainder, and so it 
            //ends up having a random number starting from 0 to dimY.
            MovingCar.push_back(new MovingCars());//puts a new MovingCars object in the 
            //MovingCar vector
            MovingCar[i]->add_pos(e1,e2);//puts a random location within the world's boundaries 
            //into the MovingCars object
        };
        for(int i=0 ; i<numMovingBikes ; i++){//This is the same thing I did before but this 
            //time for MovingBikes   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            MovingBike.push_back(new MovingBikes());
            MovingBike[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numParkedCars ; i++){ //This is the same thing I did before but this 
            //time for StationaryVehicles     
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            StationaryVehicle.push_back(new StationaryVehicles());
            StationaryVehicle[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numStopSigns ; i++){//This is the same thing I did before but this 
            //time for TrafficSigns (stop)      
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficSign.push_back(new TrafficSigns(true));
            TrafficSign[i]->add_pos(e1,e2);
        };
        for(int i=numStopSigns ; i<numSigns+numStopSigns ; i++){//This is the same thing I did before but this 
            //time for TrafficSigns   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficSign.push_back(new TrafficSigns(false));
            TrafficSign[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numTraficLights ; i++){//This is the same thing I did before but this 
            //time for TrafficLights      
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficLight.push_back(new TrafficLights());
            TrafficLight[i]->add_pos(e1,e2);
        };
};
void GridWorld::visualization_full(tuple<int, int> Self_Driving_Car_pos,char Self_Driving_Car_glyph){
        vector<WorldObject*> GridWorld[dimX][dimY];
        //puts all the objects in the GridWorld in the corresponding position based on their position
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in())GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in())GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
        };
        for(int i=0 ; i<numParkedCars ; i++){
            GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
        };
        for(int i=0 ; i<numStopSigns+numSigns ; i++){ 
            GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
        };
        for(int i=0 ; i<numTraficLights ; i++){
            GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
        };
         for(int x=0;x<dimX+2;x++){cout <<"X";};//prints the upper borders of the world
         cout <<endl;
        for(int y=dimY-1;y>=0;y--){
            cout <<"X";//prints the left border of the world
            for(int x=0;x<dimX;x++){
                if(!((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()==0)cout <<'.';//If the cell is empty, it prints .
                if(GridWorld[x][y].size()>=2)cout <<"(";//If the cell has many objects then place them in ()
                for(size_t f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();//prints the objects glyphs
                };
                if(GridWorld[x][y].size()>=2)cout<<")";
                };
                if(((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){//if the car is in this position then use it as an object
                if(GridWorld[x][y].size()>=1)cout <<"(";
                 cout <<Self_Driving_Car_glyph;//prints the car glyph
                for(size_t f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=1)cout<<")";
                };
            };
            cout <<"X";//prints the right border of the world
            cout <<endl;
        };
        for(int x=0;x<dimX+2;x++){cout <<"X";};//prints the lowest border of the world
        cout <<endl;
};
void GridWorld::NEW_tick(){
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in()){//if the MovingCar is within the borders
                MovingCar[i]->move();//moves the MovingCar
                if(MovingCar[i]->get_x_pos()>=dimX){//if the MovingCar is outside the border
                    MovingCar[i]->not_in();
                };
               if(MovingCar[i]->get_y_pos() >=dimY){//if the MovingCar is outside the border
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_x_pos()<0){//if the MovingCar is outside the border
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_y_pos() <0){//if the MovingCar is outside the border
                    MovingCar[i]->not_in();
                };
            };
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in()){//if the MovingBike is within the borders
                MovingBike[i]->move();//moves the MovingBike
                if(MovingBike[i]->get_x_pos()>=dimX){//if the MovingBike is outside the border
                    MovingBike[i]->not_in();;
                };
                if(MovingBike[i]->get_y_pos() >=dimY){//if the MovingBike is outside the border
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_x_pos()<0){//if the MovingBike is outside the border
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_y_pos() <0){//if the MovingBike is outside the border
                    MovingBike[i]->not_in();
                };
            };
        };
    for(int i=0 ; i<numTraficLights ; i++){
        TrafficLight[i]->new_cycle();//updates the TrafficLight tick 
     };
};
vector<WorldObject*> GridWorld::get_GridWorld()const{//it returns an veνctor with all the Objects
        vector<WorldObject*> GridWorld;
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in())GridWorld.push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
           if(MovingBike[i]->get_in())GridWorld.push_back(MovingBike[i]);
        };
        for(int i=0 ; i<numParkedCars ; i++){
            GridWorld.push_back(StationaryVehicle[i]);
        };
        for(int i=0 ; i<numStopSigns+numSigns ; i++){ 
            GridWorld.push_back(TrafficSign[i]);
        };
        for(int i=0 ; i<numTraficLights ; i++){
            GridWorld.push_back(TrafficLight[i]); 
        };
        return GridWorld;
};
    void GridWorld::visualization_pov(tuple<int, int> Self_Driving_Car_pos,char Self_Driving_Car_glyph,int radius){
                vector<WorldObject*> GridWorld[dimX][dimY];
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in())GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in())GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
        };
        for(int i=0 ; i<numParkedCars ; i++){
            GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
        };
        for(int i=0 ; i<numStopSigns+numSigns ; i++){ 
            GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
        };
        for(int i=0 ; i<numTraficLights ; i++){
            GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
        };
        //works exactly like the corispoding part in visualization_full but it check for every print
        //by calculate the distance if the distance is less than the radius then display the object if its not then it
        ////display an empty space " " 
         for(int x=-1;x<dimX+1;x++){
            if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-dimY)<=radius)cout <<"X";
            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-dimY)<=radius))cout <<" ";
        };
         cout <<endl;
        for(int y=dimY-1;y>=0;y--){
            if(apolito(get<0>(Self_Driving_Car_pos)+1)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius)cout <<"X";
            if(!(apolito(get<0>(Self_Driving_Car_pos)+1)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius))cout <<" ";
            for(int x=0;x<dimX;x++){
            if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius){
                if(!((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()==0)cout <<'.';
                if(GridWorld[x][y].size()>=2)cout <<"(";
                for(size_t f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=2)cout<<")";
                };
                if(((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()>=1)cout <<"(";
                 cout <<Self_Driving_Car_glyph;
                for(size_t f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=1)cout<<")";
                };
            };
            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius))cout <<" ";
            };
            if(apolito(get<0>(Self_Driving_Car_pos)-dimX)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius)cout <<"X";
            if(!(apolito(get<0>(Self_Driving_Car_pos)-dimX)+apolito(get<1>(Self_Driving_Car_pos)-y)<=radius))cout <<" ";
            cout <<endl;
        };
        for(int x=-1;x<dimX+1;x++){if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)+1)<=radius)cout <<"X";
            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)+1)<=radius))cout <<" ";
        };
        cout <<endl;


    };
    void GridWorld::visualization_pov_front(tuple<int, int> Self_Driving_Car_pos,char Self_Driving_Car_glyph,CarDirection direction){
                vector<WorldObject*> GridWorld[dimX][dimY];
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in())GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in())GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
        };
        for(int i=0 ; i<numParkedCars ; i++){
            GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
        };
        for(int i=0 ; i<numStopSigns+numSigns ; i++){ 
            GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
        };
        for(int i=0 ; i<numTraficLights ; i++){
            GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
        };
        //works exactly like the corispoding part in visualization_full but thes time it check for every print
        //by calculate the distance if the distance is less than the field of vision and then it checks if it is in 
        //front of the car (depends on the direction of the car) display the object if its not then it 
        //display an empty space " " 
         for(int x=-1;x<dimX+1;x++){
            if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-dimY)<= 12){
                if(direction== CarDirection::NORTH){
                    if((get<0>(Self_Driving_Car_pos)==x))cout <<"X";
                    if(!(get<0>(Self_Driving_Car_pos)==x))cout <<" ";
                };
                if(direction== CarDirection::EAST){cout <<" ";};
                if(direction== CarDirection::WEST){cout <<" ";};
                if(direction== CarDirection::SOUTH){cout <<" ";};
                
            };

            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-dimY)<= 12))cout <<" ";
        };
         cout <<endl;
        for(int y=dimY-1;y>=0;y--){
            if(apolito(get<0>(Self_Driving_Car_pos)+1)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12){
                if(direction== CarDirection::NORTH)cout <<" ";
                if(direction== CarDirection::EAST){cout <<" ";};
                if(direction== CarDirection::WEST){
                    if((get<1>(Self_Driving_Car_pos)==y))cout <<"X";
                    if(!(get<1>(Self_Driving_Car_pos)==y))cout <<" ";
                };
                if(direction== CarDirection::SOUTH){cout <<" ";};
                
            };
            if(!(apolito(get<0>(Self_Driving_Car_pos)+1)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12))cout <<" ";
            for(int x=0;x<dimX;x++){
            if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12){
                if(!((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                    bool in=false;
                    if(direction== CarDirection::NORTH){
                    if((get<1>(Self_Driving_Car_pos)>=y)&&(get<0>(Self_Driving_Car_pos)==x))in=true;
                    if(!((get<1>(Self_Driving_Car_pos)>=y)&&(get<0>(Self_Driving_Car_pos)==x)))cout <<" ";
                };
                if(direction== CarDirection::EAST){
                    if((get<1>(Self_Driving_Car_pos)==y)&&(get<0>(Self_Driving_Car_pos)>=x))in=true;
                    if(!((get<1>(Self_Driving_Car_pos)==y)&&(get<0>(Self_Driving_Car_pos)>=x)))cout <<" ";
                };
                if(direction== CarDirection::WEST){
                    if((get<1>(Self_Driving_Car_pos)==y)&&(get<0>(Self_Driving_Car_pos)<=x))in=true;
                    if(!((get<1>(Self_Driving_Car_pos)==y)&&(get<0>(Self_Driving_Car_pos)<=x)))cout <<" ";
                };
                if(direction== CarDirection::SOUTH){
                    if((get<1>(Self_Driving_Car_pos)<=y)&&(get<0>(Self_Driving_Car_pos)==x))in=true;
                    if(!((get<1>(Self_Driving_Car_pos)<=y)&&(get<0>(Self_Driving_Car_pos)==x)))cout <<" ";
                };
                if(in==true){
                    if(GridWorld[x][y].size()==0)cout <<'.';
                    if(GridWorld[x][y].size()>=2)cout <<"(";
                    for(size_t f=0;f<GridWorld[x][y].size();f++){
                        cout <<(GridWorld[x][y])[f]->GET_glyph();
                    };
                    if(GridWorld[x][y].size()>=2)cout<<")";
                };
                };
                if(((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()>=1)cout <<"(";
                 cout <<Self_Driving_Car_glyph;
                for(size_t f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=1)cout<<")";
                };
            };
            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12))cout <<" ";
            };
            
            if(apolito(get<0>(Self_Driving_Car_pos)-dimX)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12){
                if(direction== CarDirection::NORTH)cout <<" ";
                if(direction== CarDirection::EAST){cout <<" ";};
                if(direction== CarDirection::WEST){
                    if((get<1>(Self_Driving_Car_pos)==y))cout <<"X";
                    if(!(get<1>(Self_Driving_Car_pos)==y))cout <<" ";
                };
                if(direction== CarDirection::SOUTH){cout <<" ";};
                
            };
            if(!(apolito(get<0>(Self_Driving_Car_pos)-dimX)+apolito(get<1>(Self_Driving_Car_pos)-y)<= 12))cout <<" ";
            cout <<endl;
        };
        for(int x=-1;x<dimX+1;x++){
            if(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)+1)<= 12){
                if(direction== CarDirection::NORTH){
                    if((get<0>(Self_Driving_Car_pos)==x))cout <<"X";
                    if(!(get<0>(Self_Driving_Car_pos)==x))cout <<" ";
                };
                if(direction== CarDirection::EAST){cout <<" ";};
                if(direction== CarDirection::WEST){cout <<" ";};
                if(direction== CarDirection::SOUTH){cout <<" ";};
                
            };
            if(!(apolito(get<0>(Self_Driving_Car_pos)-x)+apolito(get<1>(Self_Driving_Car_pos)+1)<= 12))cout <<" ";
        };
        cout <<endl;


    };
GridWorld::~GridWorld(){//deletes all the one by one objects
        for(int i=0 ; i<numMovingCars ; i++){
            delete MovingCar[i];
        };
        for(int i=0 ; i<numMovingBikes ; i++){
            delete MovingBike[i];
        };
        for(int i=0 ; i<numParkedCars ; i++){
            delete StationaryVehicle[i];
        };
        for(int i=0 ; i<numStopSigns+numSigns ; i++){   
            delete TrafficSign[i];
        };
        for(int i=0 ; i<numTraficLights ; i++){
            delete TrafficLight[i];
        };
};