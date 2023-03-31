#include <Arduino.h>
#include "routine.h"

DC2W car;

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
