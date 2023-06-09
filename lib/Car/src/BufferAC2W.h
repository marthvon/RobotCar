#pragma once
#include <Arduino.h>

#include "AC2W.h"
#define ASYNC

namespace Car {
    namespace Buffer {
        enum class COMMAND {
            RESET,
            SPEED,
            ANGLE
        };

        class BufferAC2W {
        public:
            struct Instruction {
                const unsigned long delay;
                const COMMAND* const list;
                const uint8_t cmd_length;
                const float* const parameters;
                Instruction* next = nullptr;
                
                Instruction(const unsigned long p_delay, const COMMAND* const p_list, const uint8_t length, const float* const p_parameters);
                ~Instruction();
            };
        private:
            AnalogCar2W* car;
            const bool isOwned;
            unsigned long tick = 0;

            #ifdef ASYNC
                int async_protection = 0;
            #endif
            Instruction* root = nullptr;
            Instruction* back = nullptr;
            void addBuffer(Instruction* p_instruction);
        public:
            BufferAC2W(AnalogCar2W& p_car);
            BufferAC2W(AnalogCar2W&& p_car);
            BufferAC2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel);
            ~BufferAC2W();

            void begin();
            void run(const unsigned long delta);
            AnalogCar2W* get_car() const;

            void buffer_reset(const unsigned long after_ms);
            void buffer_speed_angle(const unsigned long after_ms, const float speed, const float angle);
            void buffer_speed(const unsigned long after_ms, const float speed, const bool isReset = false);
            void buffer_angle(const unsigned long after_ms, const float angle, const bool isReset = false);
        };
    };
};