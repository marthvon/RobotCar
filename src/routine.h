#pragma once
#include <Car.h>

using DC2W = DigitalCar2W<6,9,11,10>;
#include <Car.cpp> //weird 'undefined reference error' that I have no idea why. My guess the Car.cpp should be compiled to a static library like lnk

void my_routine(DC2W& car) {
    //example:
    //forward
    car.setGo(true);
    car.run();
    delay(1000);
    //left forward
    car.setStir(DC2W::STIR::LEFT);
    car.run();
    delay(1000);
    //right forward
    car.setStir(DC2W::STIR::RIGHT);
    car.run();
    delay(1000);
    //right backward
    car.setReverse(true);
    car.run();
    delay(1000);
    //left backward
    car.setStir(DC2W::STIR::LEFT);
    car.run();
    delay(1000);
    //backward
    car.setStir(DC2W::STIR::NEUTRAL);
    car.run();
    delay(1000);

    car.setGo(false);
    car.setReverse(false);
    delay(1000);
}

void dance(DC2W& car) {

}