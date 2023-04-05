#pragma once
#include <Arduino.h>

#include "DC2W.h"
#define ASYNC

namespace Car {
    namespace Buffer {
        enum class COMMAND {
            RESET,
            GO,
            REVERSE,
            STIR
        };

        class BufferDC2W {
        public:
            struct Instruction {
                const unsigned long delay;
                const COMMAND* const list;
                const uint8_t cmd_length;
                const int* const parameters;
                Instruction* next = nullptr;
                
                Instruction(const unsigned long p_delay, const COMMAND* const p_list, const uint8_t length, const int* const p_parameters);
            };
        private:
            DigitalCar2W* car;
            const bool isOwned;
            unsigned long tick = 0;

            #ifdef ASYNC
                int async_protection = 0;
            #endif
            Instruction* root = nullptr;
            Instruction* back = nullptr;
            void addBuffer(Instruction* p_instruction);
        public:
            BufferDC2W(DigitalCar2W& car);
            BufferDC2W(DigitalCar2W&& car);
            BufferDC2W(const uint8_t p_forwardLeftWheel, const uint8_t p_backwardLeftWheel, const uint8_t p_forwardRightWheel, const uint8_t p_backwardRightWheel);
            ~BufferDC2W();

            void begin();
            void run(const unsigned long delta);
            DigitalCar2W* get_car() const;

            void buffer_reset(const unsigned long after_ms);
            void buffer_go(const unsigned long after_ms, const bool go, const bool isReset = false);
            void buffer_reverse(const unsigned long after_ms, const bool reverse, const bool isReset = false);
            void buffer_stir(const unsigned long after_ms, const STIR stir, const bool isReset = false);
            void buffer_go_reverse(const unsigned long after_ms,const bool go, const bool reverse, const bool isReset = false);
            void buffer_go_stir(const unsigned long after_ms, const bool go, const STIR stir, const bool isReset = false);
            void buffer_reverse_stir(const unsigned long after_ms, const bool reverse, const STIR stir, const bool isReset = false);
            void buffer_go_reverse_stir(const unsigned long after_ms, const bool go, const bool reverse, const STIR stir);
        };        
    };
};