#pragma once
#include <Arduino.h>

namespace Car {
    enum class STIR {
        RIGHT = 1,
        LEFT,
        NEUTRAL
    };

    class DigitalCar2W {
        struct Wheel {
            const uint8_t leftForward;
            const uint8_t leftBackward;
            const uint8_t rightForward;
            const uint8_t rightBackward;

            constexpr Wheel(const uint8_t p_leftForward, const uint8_t p_leftBackward, const uint8_t p_rightForward, const uint8_t p_rightBackward) 
                : leftForward(p_leftForward), leftBackward(p_leftBackward), rightForward(p_rightForward), rightBackward(p_rightBackward) {}
        } const wheel;

        /**
         * @brief 8-bits of toggles
         *      1st & 2nd bit: stir_left(10) or keep_center(11) or stir_right(01)
         *      3rd bit: isReverse(1) or isNotReverse(0)
         *      4th bit: (1) should update on run or not (0)
         *      5th bit: go(0) or stop(1)
         */
        uint8_t data = 0b00001011; 

        inline const bool isGo();
        inline const bool isReverse();
        inline const bool isLeft();
        inline const bool isRight(); 
    public:
        DigitalCar2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel);
        DigitalCar2W(DigitalCar2W& other);
        void begin();
        void run();
        void reset();

        void setGo(const bool p_go);
        void setReverse(const bool p_reverse);
        void setStir(const STIR p_stir); 
    };
};