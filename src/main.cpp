#include <Arduino.h>
#include <routine.h>

DigitalCar2W car(6,9,11,10);

void setup() {
  car.begin();
  
  car.reset();
  car.run();
  delay(5000);
}

void loop() {
  //my_routine(car);
  dance(car);
}
