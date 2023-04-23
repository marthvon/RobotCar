#pragma once
#include <Arduino.h>

namespace Car {
    class AnalogCar2W {
        struct Wheel {
            const uint8_t leftForward;
            const uint8_t leftBackward;
            const uint8_t rightForward;
            const uint8_t rightBackward;

            constexpr Wheel(const uint8_t p_leftForward, const uint8_t p_leftBackward, const uint8_t p_rightForward, const uint8_t p_rightBackward) 
                : leftForward(p_leftForward), leftBackward(p_leftBackward), rightForward(p_rightForward), rightBackward(p_rightBackward) {}
        } const wheel;

        float speed = 0;
        float angle = 0;
        bool isUpdate = true;

        void update() const;
    public:
        AnalogCar2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel);
        AnalogCar2W(const AnalogCar2W& other);
        void begin();
        void run();
        void reset();

        void setSpeed(const float p_speed);
        void setAngle(const float p_rad);
    };
};