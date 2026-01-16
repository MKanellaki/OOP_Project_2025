#include "include/GridWorld.h"
#include "include/radarSensor.h"
#include "include/lidarSensor.h"
#include "include/cameraSensor.h"
#include "include/selfDrivingCar.h"
#include "include/navigationSystem.h"

#include "TrafficLights.h"
#include "StationaryVehicles.h"
#include "TrafficSigns.h"
#include "MovingBikes.h"
#include "MovingCars.h"

int TrafficLights::TrafficLightscount = 0;
int StationaryVehicles::ParkedCarcount = 0;
int TrafficSigns::TrafficSignscount = 0;
int TrafficSigns::TrafficSignsSTOPcount = 0;
int MovingBikes::MovingBikescount = 0;
int MovingCars::MovingCarscount = 0;


int main(){
    GridWorld world;
    world.set_dimX(10);
    world.set_dimY(10);
    world.set_simulationTicks(10);
    world.create_GridWorld();

    SelfDrivingCar car(0,0,CarDirection::NORTH);

    LidarSensor lidar;
    CameraSensor camera;
    RadarSensor radar;

    NavigationSystem nav;
    nav.setGPSTargets({{9,9}});

    for(int t=0; t<world.get_simulationTicks(); t++){
        auto [x,y] = car.get_position();

        lidar.updatePosition(x,y);
        camera.updatePosition(x,y);
        radar.updatePosition(x,y);

        lidar.updateDirection(car.get_direction());
        camera.updateDirection(car.get_direction());
        radar.updateDirection(car.get_direction());

        vector<SensorReading> all;
        auto l = lidar.scan(world);
        auto c = camera.scan(world);
        auto r = radar.scan(world);

        all.insert(all.end(), l.begin(), l.end());
        all.insert(all.end(), c.begin(), c.end());
        all.insert(all.end(), r.begin(), r.end());

        nav.updateSensorData(all);
        nav.makeDecision(car);

        car.move();

        if(t==0)
            world.first_tick(car.get_position(), string(1,car.get_glyph()));
        else
            world.NEW_tick(car.get_position(), string(1,car.get_glyph()));
    }
}
