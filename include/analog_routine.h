#pragma once
#include <AC2W.h>

using namespace Car;

inline void my_routine(AnalogCar2W& car) {
    //example:
    for(float i = 0; i <= 1; i += 0.01) {
        car.setSpeed(i);
        car.run();
        delay(10);
    }
    
    for(float i = 0; i >= -1; i -= 0.01) {
        car.setSpeed(i);
        car.run();
        delay(10);
    }

    car.setSpeed(1);
    for(float i = 0; i < PI; i += 0.01) {
        car.setAngle(i);
        car.run();
        delay(10);
    }
    for(float i = 0; i > PI; i -= 0.01) {
        car.setAngle(i);
        car.run();
        delay(10);
    }
    
    car.setSpeed(-1);
    for(float i = 0; i < PI; i += 0.01) {
        car.setAngle(i);
        car.run();
        delay(10);
    }
    for(float i = 0; i > PI; i -= 0.01) {
        car.setAngle(i);
        car.run();
        delay(10);
    }
}