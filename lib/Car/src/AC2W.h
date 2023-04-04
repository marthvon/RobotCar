#pragma once
#include <Arduino.h>

namespace Car {
    class AnalogCar2W {
        const uint8_t forwardLeftWheel;
        const uint8_t backwardLeftWheel;
        const uint8_t forwardRightWheel;
        const uint8_t backwardRightWheel;

        float speed;
        float angle;
        bool isUpdate = false;

        void update() const;
    public:
        AnalogCar2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel);
        void begin() const;
        void run();
        void reset();

        void setSpeed(const float p_speed);
        void setAngle(const float p_rad);
    };
};