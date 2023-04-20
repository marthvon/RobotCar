#pragma once
#include <DC2W.h>

using namespace Car;

void my_routine(DigitalCar2W& car) {
    //example:
    //forward
    car.setGo(true);
    car.run();
    delay(1000);
    //left forward
    car.setStir(STIR::LEFT);
    car.run();
    delay(1000);
    //right forward
    car.setStir(STIR::RIGHT);
    car.run();
    delay(1000);
    //right backward
    car.setReverse(true);
    car.run();
    delay(1000);
    //left backward
    car.setStir(STIR::LEFT);
    car.run();
    delay(1000);
    //backward
    car.setStir(STIR::NEUTRAL);
    car.run();
    delay(1000);

    car.reset();
    car.run();
    delay(1000);
}

void dance(DigitalCar2W& car) {
    //137 bpm per minute song
    car.setGo(true);
    car.setStir(STIR::RIGHT);
    car.run();
    delay(448);
    
    car.setStir(STIR::LEFT);
    car.run();
    delay(448);

    car.setStir(STIR::NEUTRAL);
    car.setReverse(true);
    car.run();
    delay(448);

    car.setReverse(false);
    car.setStir(STIR::LEFT);
    car.run();
    delay(448);

    car.setReverse(true);
    car.setStir(STIR::RIGHT);
    car.run();
    delay(446);
    
    car.setReverse(false);
    car.run();
    delay(448);

    car.setReverse(true);
    car.setStir(STIR::LEFT);
    car.run();
    delay(448);

    car.setReverse(false);
    car.run();
    delay(448);

    car.setStir(STIR::NEUTRAL);
    car.setReverse(true);
    car.run();
    delay(448);

    car.setReverse(false);
    car.run();
    delay(446);
}