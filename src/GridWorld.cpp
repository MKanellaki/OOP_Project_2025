#include "../include/GridWorld.h"
    int GridWorld::get_seed(){
        return seed;
    }; 
    void GridWorld::set_seed(int NEWseed){
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
    int GridWorld::get_simulationTicks(){
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
void GridWorld::create_GridWorld(){
        srand(seed);
        for(int i=0 ; i<numMovingCars ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            MovingCar.push_back(new MovingCars());
            MovingCar[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numMovingBikes ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            MovingBike.push_back(new MovingBikes());
            MovingBike[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numParkedCars ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            StationaryVehicle.push_back(new StationaryVehicles());
            StationaryVehicle[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numStopSigns ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficSign.push_back(new TrafficSigns(true));
            TrafficSign[i]->add_pos(e1,e2);
        };
        for(int i=numStopSigns ; i<numSigns+numStopSigns ; i++){
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficSign.push_back(new TrafficSigns(false));
            TrafficSign[i]->add_pos(e1,e2);
        };
        for(int i=0 ; i<numTraficLights ; i++){   
            int e1 =rand()%(dimX);
            int e2 =rand()%(dimY);
            TrafficLight.push_back(new TrafficLights());
            TrafficLight[i]->add_pos(e1,e2);
        };
};
void GridWorld::first_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph){
        vector<WorldObject*> GridWorld[dimX][dimY];
        for(int i=0 ; i<numMovingCars ; i++){
            GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
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
        
        for(int y=dimY-1;y>=0;y--){
            for(int x=0;x<dimX;x++){
                if(!((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()==0)cout <<'.';
                if(GridWorld[x][y].size()>=2)cout <<"(";
                for(int f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=2)cout<<")";
                };
                if(((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
                if(GridWorld[x][y].size()>=1)cout <<"(";
                 cout <<Self_Driving_Car_glyph;
                for(int f=0;f<GridWorld[x][y].size();f++){
                    cout <<(GridWorld[x][y])[f]->GET_glyph();
                };
                if(GridWorld[x][y].size()>=1)cout<<")";
                };
            };
            cout <<endl;
        };
};
void GridWorld::NEW_tick(tuple<int, int> Self_Driving_Car_pos,string Self_Driving_Car_glyph){
        vector<WorldObject*> GridWorld[dimX][dimY];
        cout <<"\n"<<endl;
        cout <<"\n"<<endl;
        for(int i=0 ; i<numMovingCars ; i++){
            if(MovingCar[i]->get_in()){
                MovingCar[i]->move();
                if(MovingCar[i]->get_x_pos()>=dimX){
                    MovingCar[i]->not_in();
                };
               if(MovingCar[i]->get_y_pos() >=dimY){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_x_pos()<0){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_y_pos() <0){
                    MovingCar[i]->not_in();
                };
                if(MovingCar[i]->get_in()){
                    GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
                };
            };
        };
        for(int i=0 ; i<numMovingBikes ; i++){ 
            if(MovingBike[i]->get_in()){
                MovingBike[i]->move();
                if(MovingBike[i]->get_x_pos()>=dimX){
                    MovingBike[i]->not_in();;
                };
                if(MovingBike[i]->get_y_pos() >=dimY){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_x_pos()<0){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_y_pos() <0){
                    MovingBike[i]->not_in();
                };
                if(MovingBike[i]->get_in()){
                    GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
                };
            };
        };
    for(int i=0 ; i<numParkedCars ; i++){
        GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
    };
    for(int i=0 ; i<numStopSigns+numSigns ; i++){ 
        GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
    };
    for(int i=0 ; i<numTraficLights ; i++){
        TrafficLight[i]->new_cycle();
        GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
    };
    for(int y=dimY-1;y>=0;y--){
        for(int x=0;x<dimX;x++){
            if(!((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y))){
            if(GridWorld[x][y].size()==0)cout <<'.';
            if(GridWorld[x][y].size()>=2)cout <<"(";
            for(int f=0;f<GridWorld[x][y].size();f++){
                cout <<(GridWorld[x][y])[f]->GET_glyph();
            };
            if(GridWorld[x][y].size()>=2)cout<<")";
            };
            if((get<0>(Self_Driving_Car_pos)==x)&&(get<1>(Self_Driving_Car_pos)==y)){
            if(GridWorld[x][y].size()>=1)cout <<"(";
            cout <<Self_Driving_Car_glyph;
            for(int f=0;f<GridWorld[x][y].size();f++){
                cout <<(GridWorld[x][y])[f]->GET_glyph();
            };
            if(GridWorld[x][y].size()>=1)cout<<")";
            };
        };
        cout <<endl;
    };
};
vector<WorldObject*> GridWorld::get_GridWorld(){
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
GridWorld::~GridWorld(){
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