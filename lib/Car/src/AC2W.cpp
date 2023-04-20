#include "AC2W.h"

using namespace Car;

constexpr AnalogCar2W::AnalogCar2W(
    const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, 
    const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel
) : forwardLeftWheel(p_forwardLeftWheel), backwardLeftWheel(p_backwardLeftWheel), 
    forwardRightWheel(p_forwardRightWheel), backwardRightWheel(p_backwardRightWheel)
{}
constexpr AnalogCar2W::AnalogCar2W(const AnalogCar2W& other) 
    : forwardLeftWheel(other.forwardLeftWheel), backwardLeftWheel(other.backwardLeftWheel), 
      forwardRightWheel(other.forwardRightWheel), backwardRightWheel(other.backwardRightWheel)
{} 

void AnalogCar2W::begin() {
    pinMode(forwardLeftWheel, OUTPUT);
    pinMode(backwardLeftWheel, OUTPUT);
    pinMode(forwardRightWheel, OUTPUT);
    pinMode(backwardRightWheel, OUTPUT);

    #ifdef DEBUG
        hasInit = true;
    #endif
}

void AnalogCar2W::run() {
    #ifdef DEBUG
        if(!hasInit) {
            Serial.println("[Error]: Pinmodes have not been initialized for this instance of AnalogCar2W.\n\tThe \"run\" methods operation were stopped\n");
            return;    
        }
    #endif

    if(!isUpdate)
        return;
    isUpdate = false;
    if(speed == 0.0) {
        digitalWrite(forwardLeftWheel, LOW);
        digitalWrite(backwardLeftWheel, LOW);
        digitalWrite(forwardRightWheel, LOW);
        digitalWrite(backwardRightWheel, LOW);
        return;
    }
    update();
}

void AnalogCar2W::reset() {
    speed = 0;
    angle = 0;
    isUpdate = true;
}

void AnalogCar2W::update() const { 
    const uint8_t s = speed > 0? speed : -speed;
    float a = cos(angle);
    //                        if go forward? if stir left? dampen speed  else go backward? if stir right? dampen speed... otherwise just go full speed
    const uint8_t sl = 255 * (speed > 0? (angle < 0? (a<0?-a:a): 1.0) : (angle > 0? (a<0?-a:a): 1.0)) * s;
    //                        if go forward? if stir right? dampen speed  else go backward? if stir left? dampen speed... otherwise just go full speed
    const uint8_t sr = 255 * (speed > 0? (angle > 0? (a<0?-a:a): 1.0) : (angle < 0? (a<0?-a:a): 1.0)) * s;

    //if go forward and stir staight or right(+) else stir left(-) but angle<=90deg... otherwise go backward but stir right(+) and angle>90deg
    if(speed < 0? (a < 0 && angle > 0) : (angle >= 0 || a >= 0)) {
        analogWrite(forwardLeftWheel, sl); 
        digitalWrite(backwardLeftWheel, LOW);
    } else { // speed < 0 && (angle <= 0 || a >= 0)
        digitalWrite(forwardLeftWheel, LOW);
        analogWrite(backwardLeftWheel, sl);         
    }
    //if go forward and stir staight or left(-) else stir right(+) but angle<=90deg... otherwise go backward but stir left(-) and angle>90deg
    if(speed < 0? (a < 0 && angle < 0) : (angle <= 0 || a >= 0)) {
        analogWrite(forwardRightWheel, sl); 
        digitalWrite(backwardRightWheel, LOW);
    } else {
        digitalWrite(forwardRightWheel, LOW);
        analogWrite(backwardRightWheel, sl);
    }
}

void AnalogCar2W::setSpeed(const float p_speed) {
    speed = p_speed;
    isUpdate = true;
}

void AnalogCar2W::setAngle(const float p_angle) {
    angle = p_angle;
    isUpdate = true;
}
