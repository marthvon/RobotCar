#include <Arduino.h>
#include "routine.h"

DC2W car;

void setup() {
  car.begin();
}

void loop() {
  my_routine(car);
}
