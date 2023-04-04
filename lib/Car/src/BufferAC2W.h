#pragma once
#include <Arduino.h>

#include "AC2W.h"

namespace Car {
    namespace Buffer {
        class BufferAC2W {
        public:
            enum class COMMAND {
                RESET,
                SPEED,
                ANGLE
            };
        private:
            class Instruction {
                const unsigned long delay;
                const COMMAND* list;
                const float* parameters;
                Instruction* next;
            public:
                Instruction();
                Instruction* execute();
            };

            AnalogCar2W* car;
            const bool isOwned;

            Instruction* root = nullptr;
            Instruction* back = nullptr;
        public:
            BufferAC2W(AnalogCar2W& p_car);
            BufferAC2W(AnalogCar2W&& p_car);
            ~BufferAC2W();

            void begin();
            void run();
            void addBuffer();
        };
    };
};