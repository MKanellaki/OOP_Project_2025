#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <string>

#include "include/GridWorld.h"
#include "include/radarSensor.h"
#include "include/lidarSensor.h"
#include "include/cameraSensor.h"
#include "include/selfDrivingCar.h"
#include "include/navigationSystem.h"

using namespace std;

void printHelp(){
    cout << "Self-Driving Car Simulation\n";
    cout << "Usage:\n";
    cout << "  --seed <n>                     Random seed (default: current time)\n";
    cout << "  --dimX <n>                     World width (default: 40)\n";
    cout << "  --dimY <n>                     World height (default: 40)\n";
    cout << "  --numMovingCars <n>            Number of moving cars (default: 3)\n";
    cout << "  --numMovingBikes <n>           Number of moving bikes (default: 4)\n";
    cout << "  --numParkedCars <n>            Number of parked cars (default: 5)\n";
    cout << "  --numStopSigns <n>             Number of stop signs (default: 2)\n";
    cout << "  --numTrafficLights <n>         Number of traffic lights (default: 2)\n";
    cout << "  --simulationTicks <n>          Maximum simulation ticks (default: 100)\n";
    cout << "  --minConfidenceThreshold <f>   Minimum confidence cutoff (default: 0.4)\n";
    cout << "  --gps <x1> <y1> [x2 y2 ...]    GPS target coordinates (required)\n";
    cout << "  --help                         Show this help message\n\n";
    cout << "Example:\n";
    cout << "  ./oopproj_2025 --seed 12 --dimY 50 --gps 10 20 32 15\n";
}

int main(int argc, char* argv[]){
    //DEFAULT PARAMETERS
    int seed = time(nullptr);
    int dimX = 30;
    int dimY = 30;
    int simulationTicks = 100;

    int numMovingCars = 3;
    int numMovingBikes = 4;
    int numParkedCars = 5;
    int numStopSigns = 2;
    int numTrafficLights = 2;

    float minConfidenceThreshold = 0.4f;
    vector<tuple<int,int>> gpsTargets;

    //ARGUMENTS
    for(int i = 1; i < argc; ++i){
        string arg = argv[i];

        if(arg == "--help"){
            printHelp();
            return 0;
        }
        else if(arg == "--seed" && i + 1 < argc){
            seed = atoi(argv[++i]);
        }
        else if(arg == "--dimX" && i + 1 < argc){
            dimX = atoi(argv[++i]);
        }
        else if(arg == "--dimY" && i + 1 < argc){
            dimY = atoi(argv[++i]);
        }
        else if(arg == "--numMovingCars" && i + 1 < argc){
            numMovingCars = atoi(argv[++i]);
        }
        else if(arg == "--numMovingBikes" && i + 1 < argc){
            numMovingBikes = atoi(argv[++i]);
        }
        else if(arg == "--numParkedCars" && i + 1 < argc){
            numParkedCars = atoi(argv[++i]);
        }
        else if(arg == "--numStopSigns" && i + 1 < argc){
            numStopSigns = atoi(argv[++i]);
        }
        else if(arg == "--numTrafficLights" && i + 1 < argc){
            numTrafficLights = atoi(argv[++i]);
        }
        else if(arg == "--simulationTicks" && i + 1 < argc){
            simulationTicks = atoi(argv[++i]);
        }
        else if(arg == "--minConfidenceThreshold" && i + 1 < argc){
            minConfidenceThreshold = stof(argv[++i]);
        }
        else if(arg == "--gps"){
            if(i + 2 >= argc){
                cerr << "Error: --gps requires at least one <x y> pair\n";
                return 1;
            }
            while(i + 2 < argc){
                int x = atoi(argv[++i]);
                int y = atoi(argv[++i]);
                gpsTargets.emplace_back(x, y);
            }
        }
        else{
            cerr << "Unknown or incomplete parameter: " << arg << endl;
            return 1;
        }
    }

    if(gpsTargets.empty()){
        cerr << "Error: At least one GPS target must be provided (--gps)\n";
        return 1;
    }

    //WORLD STETUP
    GridWorld world;
    world.set_seed(seed);
    world.set_dimX(dimX);
    world.set_dimY(dimY);
    world.set_simulationTicks(simulationTicks);
    world.set_numMovingCars(numMovingCars);
    world.set_numMovingBikes(numMovingBikes);
    world.set_numParkedCars(numParkedCars);
    world.set_numStopSigns(numStopSigns);
    world.set_numTraficLights(numTrafficLights);
    world.create_GridWorld();

    //CAR SETUP
    SelfDrivingCar car(0, 0, CarDirection::NORTH);

    LidarSensor lidar;
    CameraSensor camera;
    RadarSensor radar;

    NavigationSystem navigation(minConfidenceThreshold);
    navigation.setGPSTargets(gpsTargets);

    //SIMULATION LOOP
    for(int tick = 0; tick < simulationTicks; ++tick){
        auto [x, y] = car.get_position();

        //end simulation if car exits world
        if(x < 0 || x >= dimX || y < 0 || y >= dimY){
            cout << "Simulation ended: car exited world bounds.\n";
            break;
        }

        lidar.updatePosition(x, y);
        camera.updatePosition(x, y);
        radar.updatePosition(x, y);

        lidar.updateDirection(car.get_direction());
        camera.updateDirection(car.get_direction());
        radar.updateDirection(car.get_direction());

        vector<SensorReading> readings;
        auto l = lidar.scan(world);
        auto c = camera.scan(world);
        auto r = radar.scan(world);

        readings.insert(readings.end(), l.begin(), l.end());
        readings.insert(readings.end(), c.begin(), c.end());
        readings.insert(readings.end(), r.begin(), r.end());

        navigation.updateSensorData(readings);
        navigation.makeDecision(car);

        car.move();
        world.NEW_tick();

        if(tick == 0){
            world.visualization_full(car.get_position(), car.get_glyph());
        }else{
            //change comment for different area
            world.visualization_pov(car.get_position(), car.get_glyph(), 5);
            //world.visualization_pov_front(car.get_position(), car.get_glyph(), car.get_direction());
        }
    }

    return 0;
}
