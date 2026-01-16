# Self Driving Car GPS Navigation System


## Authors

```
Κανελλάκη Μαρία sdi2300060
Ραντίτσας Κωνσταντίνος sdi2400175
```

## Overview
This project was made for the 2025 Object-Oriented Programming Course of the University of Athens.

This project implements a discrete-time simulation of an autonomous vehicle navigating a 2D grid world. The simulation models static and dynamic world objects, multiple sensors with noise, sensor fusion, and a navigation system that guides the vehicle toward one or more GPS targets while reacting to obstacles and traffic infrastructure. 

The simulation progresses in discrete ticks, where all entities update their state simultaneously.

---

## How to Compile and Run

### Compilation
The project is written in **C++** and can be compiled using the provided makefile.

compilation:
```bash
make
````
---

### Execution

The simulation is executed via command-line arguments using parameter–value pairs.

General form:

```bash
./oopproj_2025 [parameters] --gps <x1> <y1> [x2 y2 ...]
```

The `--gps` parameter **must always be provided last** and must include **at least one target**.

---

### Supported Parameters

| Parameter                      | Description               | Default      |
| ------------------------------ | ------------------------- | ------------ |
| `--seed <n>`                   | Random seed               | current time |
| `--dimX <n>`                   | World width               | 40           |
| `--dimY <n>`                   | World height              | 40           |
| `--numMovingCars <n>`          | Number of moving cars     | 3            |
| `--numMovingBikes <n>`         | Number of moving bikes    | 4            |
| `--numParkedCars <n>`          | Number of parked cars     | 5            |
| `--numStopSigns <n>`           | Number of stop signs      | 2            |
| `--numTrafficLights <n>`       | Number of traffic lights  | 2            |
| `--simulationTicks <n>`        | Maximum simulation ticks  | 100          |
| `--minConfidenceThreshold <f>` | Minimum confidence cutoff | 0.4          |
| `--gps <x y ...>`              | GPS target coordinates    | **required** |
| `--help`                       | Print help message        | —            |

---

### Example Runs

Minimal:

```bash
./oopproj_2025 --gps 10 20
```

Full:

```bash
./oopproj_2025 --seed 12 --dimX 50 --dimY 50 --numMovingCars 5 --numTrafficLights 3 --minConfidenceThreshold 0.6 --gps 10 20 32 15
```

---

## Simulation Logic

The simulation executes in **discrete ticks**.
At each tick:

1. **World Objects Update**

   * Moving vehicles update position based on speed and direction
   * Traffic lights update their internal state
   * Static objects remain unchanged

2. **Sensor Data Collection**

   * The autonomous vehicle uses:

     * Lidar
     * Camera
     * Radar
   * Each sensor:

     * Has its own range and field of view
     * Adds noise to measurements
     * Produces a confidence value per detection

3. **Sensor Fusion**

   * Sensor readings referring to the same world object are grouped
   * Distance estimates are fused using confidence-weighted averaging
   * Readings below the confidence threshold are ignored

4. **Navigation Decision**

   * Hazards and traffic rules take priority
   * GPS targets guide direction and speed
   * The vehicle updates speed and direction accordingly

5. **Movement**

   * The vehicle moves one step
   * If it attempts to exit the world bounds, the simulation ends

The simulation ends when:

* The maximum number of ticks is reached, **or**
* The autonomous vehicle attempts to move outside the grid

---

## Coordinate System

* The world is a 2D grid of size `dimX × dimY`
* Coordinate system:

  * `(0,0)` is at the **bottom-left**
  * `x` increases to the right
  * `y` increases upward
* All positions are integer grid coordinates

---

## Assumptions & Design Decisions

* **Static objects** (parked cars, stop signs, traffic lights) have:

  * Speed = `-1` (used to indicate immobility)
* The autonomous vehicle starts at:

  * Position `(0,0)`
  * Facing `NORTH`
* `GridWorld::create_GridWorld()` is assumed to be called **once**
* World objects are randomly placed using the provided seed
* Object IDs include both type and serial number to avoid sensor fusion collisions
* Sensors do not detect the autonomous vehicle itself
* Only objects within sensor range and field of view are detected
* TrafficLights all start on red
* Moving Objects have a 3/4 chance to change direction

---

## Noise Model

Sensors simulate imperfect measurements by adding noise to the true distance.

### Noise Formula

For a true distance `d`:

```
d_noisy = d + N(0, σ)
```

Where:

* `N(0, σ)` is Gaussian noise
* `σ` depends on the sensor type
* Negative distances are clamped to zero

---

## Confidence Calculation

Each sensor reading is assigned a confidence value based on distance.

### Confidence Formula

```
confidence = max(0, 1 - (d / maxRange))
```

Where:

* `d` is the measured (noisy) distance
* `maxRange` is the sensor’s maximum detection range

Confidence values closer to `1` indicate more reliable readings.

During fusion:

* Readings with confidence `< minConfidenceThreshold` are discarded
* Remaining readings are combined using weighted averaging

---

## Visualization

Three visualization modes are provided:

* **Full World View**

  * Displays the entire grid (used at tick 0)
* **Point-of-View (POV)**

  * Displays a limited area around the vehicle

* **Point-of-View-Front (POV)**

  * Displays a limited area in front of the vehicle

