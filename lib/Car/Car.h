#pragma once
#include <Arduino.h>

template<
    uint8_t forwardLeftWheel, uint8_t backwardLeftWheel,
    uint8_t forwardRightWheel, uint8_t backwardRightWheel
> class DigitalCar2W {
    /**
     * @brief 8-bits of toggles
     *      1st & 2nd bit: stir_left(10) or keep_center(11) or stir_right(01)
     *      3rd bit: isReverse(1) or isNotReverse(0)
     *      4th bit: (1) should update on run or not (0)
     *      5th bit: go(0) or stop(1)
     */
    uint8_t data = 0b00000011; 

    inline const bool isGo();
    inline const bool isReverse();
    inline const bool isLeft();
    inline const bool isRight(); 
public:
    DigitalCar2W() {}
    void begin() const;
    void run();

    void setGo(const bool p_go);
    void setReverse(const bool p_reverse);

    enum class STIR {
        RIGHT = 1,
        LEFT,
        NEUTRAL
    };
    void setStir(const STIR p_stir); 
};

template<
    uint8_t forwardLeftWheel, uint8_t backwardLeftWheel,
    uint8_t forwardRightWheel, uint8_t backwardRightWheel
> class AnalogCar2W {
    float speed;
    float angle;
    bool isUpdate = false;

    void update() const;
public:
    AnalogCar2W() {}
    void begin() const;
    void run() const;

    void setSpeed(const float p_speed);
    void setAngle(const float p_rad);
};

