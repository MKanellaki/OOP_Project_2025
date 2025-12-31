#include <iostream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
class WorldObject{
protected:
string ID;
string glyph;
int X;//οριζόντιος άξονας 
int Y;//κάθετος άξονας
public:
void add_glyph(string x){
   glyph = x;
};
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
};
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
    };
}; 
class MovingCars : public MovingObjects{
    public:
    MovingCars(){
        in =true;
        add_glyph("C");
        speed=2;
        int f =rand()%(4);
        if (f==0)direction="left";
        if (f==1)direction="right";
        if (f==2)direction="up";
        if (f==3)direction="down";
      //  cout <<direction <<"\n"<<endl;
    };
    void describe()override{
       cout <<"MovingCars direction\n"<<endl;
       cout <<direction <<"\n"<<endl;
    };
};
class MovingBikes : public MovingObjects{
    public:
MovingBikes(){
        in =true;
        add_glyph("B");
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
class StaticObjects : public WorldObject{

};
class StationaryVehicles : public StaticObjects{
protected:
public:
    StationaryVehicles(){
        add_glyph("P");
    };
void describe()override{
       cout <<"StationaryVehicles \n"<<endl;
    };
};
class TrafficSigns : public StaticObjects{
protected:
bool is_STOP;
public:
TrafficSigns(bool STOP):is_STOP(STOP){
    add_glyph("S");
};
void describe()override{
       cout <<"TrafficSigns \n"<<endl;
       if(is_STOP)cout <<"STOP \n"<<endl;
       if(!is_STOP)cout <<"NOT STOP \n"<<endl;
    };
};
class TrafficLights : public StaticObjects{
protected:
bool RED;
bool YELLOW;
bool GREEN;
int ticksRED;
int ticksYELLOW;
int ticksGREEN;
public:
TrafficLights():RED(true),YELLOW(false),GREEN(false),ticksRED(1),ticksYELLOW(0),ticksGREEN(0){
    add_glyph("R");
};
void new_cycle(){
    if(RED)ticksRED++;
    if(YELLOW)ticksYELLOW++;
    if(GREEN)ticksGREEN++;
    if(ticksRED>4){
        add_glyph("G");
        GREEN=true;
        YELLOW=false;
        RED=false;
        ticksGREEN=1;
        ticksRED=0;
        ticksYELLOW=0;
    };
    if(ticksGREEN>8){
        add_glyph("Y");
        YELLOW=true;
        GREEN=false;
        RED=false;
        ticksGREEN=0;
        ticksRED=0;
        ticksYELLOW=1;
    };
    if(ticksYELLOW>2){
        add_glyph("R");
        RED=true;
        GREEN=false;
        YELLOW=false;
        ticksGREEN=0;
        ticksRED=1;
        ticksYELLOW=0;
    };
};
void describe()override{
       cout <<"TrafficLights \n"<<endl;
       if(RED)cout <<"RED \n"<<endl;
       if(YELLOW)cout <<"YELLOW \n"<<endl;
       if(GREEN)cout <<"GREEN \n"<<endl;
    };
};
/*
void map(vector<WorldObject*> GridWorld[40][40]){
for(int x=0;x<40;x++){
for(int y=0;y<40;y++){
if(GridWorld[x][y].size()==0)cout <<"0"<<endl;
if(GridWorld[x][y].size()>1)cout <<"("<<endl;
for(int f=0;f<GridWorld[x][y].size();f++){
cout <<(GridWorld[x][y])[f]->GET_glyph()<<endl;
};
if(GridWorld[40][40].size()>1)cout <<")"<<endl;
};
cout <<"\n"<<endl;
};
};
*/
int main(){
    srand(time(NULL));
//    40×40
int dimX = 40;
int dimY = 20;
vector<WorldObject*> GridWorld[dimX][dimY];  
int simulationTicks= 5;
/*
for(int i=0 ; i<dimX ; i++){   
for(int e=0 ; e<dimY ; e++){   
GridWorld[i][e].push_back(NULL);
};
};*/
int numMovingCars = 3 ;
int numMovingBikes = 4 ;
int numParkedCars = 5 ;
int numStopSigns = 2;
int numTraficLights = 2 ;
vector<MovingCars*> MovingCar;
vector<MovingBikes*> MovingBike;
vector<StationaryVehicles*> StationaryVehicle;
vector<TrafficSigns*> TrafficSign;
vector<TrafficLights*> TrafficLight;
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
for(int i=0 ; i<numTraficLights ; i++){   
int e1 =rand()%(dimX);
int e2 =rand()%(dimY);
TrafficLight.push_back(new TrafficLights());
TrafficLight[i]->add_pos(e1,e2);
};


for(int i=0 ; i<numMovingCars ; i++){
    GridWorld[MovingCar[i]->get_x_pos()][MovingCar[i]->get_y_pos()].push_back(MovingCar[i]);
};
for(int i=0 ; i<numMovingBikes ; i++){ 
    GridWorld[MovingBike[i]->get_x_pos()][MovingBike[i]->get_y_pos()].push_back(MovingBike[i]);
};
for(int i=0 ; i<numParkedCars ; i++){
    GridWorld[StationaryVehicle[i]->get_x_pos()][StationaryVehicle[i]->get_y_pos()].push_back(StationaryVehicle[i]);
};
for(int i=0 ; i<numStopSigns ; i++){ 
    GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
};
for(int i=0 ; i<numTraficLights ; i++){
    GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
};

for(int y=0;y<dimY;y++){
for(int x=0;x<dimX;x++){
if(GridWorld[x][y].size()==0)cout <<'_';
if(GridWorld[x][y].size()>=2)cout <<"(";
for(int f=0;f<GridWorld[x][y].size();f++){
cout <<(GridWorld[x][y])[f]->GET_glyph();
};
if(GridWorld[x][y].size()>=2)cout<<")";
};
//cout <<"\n"<<endl;
cout <<endl;
};
int size1;
for(int Ticks=1 ; Ticks<simulationTicks ; Ticks++){
 
for(int x=0;x<dimX;x++){
for(int y=0;y<dimY;y++){
size1 = GridWorld[x][y].size();
//for(int f=0;f<GridWorld[x][y].size();f++){
//GridWorld[x][y].pop_back();
GridWorld[x][y].clear();
//};
};
};
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
for(int i=0 ; i<numStopSigns ; i++){ 
    GridWorld[TrafficSign[i]->get_x_pos()][TrafficSign[i]->get_y_pos()].push_back(TrafficSign[i]);
};
for(int i=0 ; i<numTraficLights ; i++){
    TrafficLight[i]->new_cycle();
    GridWorld[TrafficLight[i]->get_x_pos()][TrafficLight[i]->get_y_pos()].push_back(TrafficLight[i]); 
};
///*
for(int y=0;y<dimY;y++){
for(int x=0;x<dimX;x++){
if(GridWorld[x][y].size()==0)cout <<'_';
if(GridWorld[x][y].size()>=2)cout <<"(";
for(int f=0;f<GridWorld[x][y].size();f++){
cout <<(GridWorld[x][y])[f]->GET_glyph();
};
if(GridWorld[x][y].size()>=2)cout<<")";
};
//cout <<"\n"<<endl;
cout <<endl;
};
//*/

};


//map(GridWorld);

/*//
for(int i=0 ; i<40 ; i++){   
for(int e=0 ; e<40 ; e++){   
    if(GridWorld[i][e]!=NULL){
        cout <<i<<"    "<<e<<"\n"<<endl;
        GridWorld[i][e]->describe();//not finish 
    };
};
};*/
};