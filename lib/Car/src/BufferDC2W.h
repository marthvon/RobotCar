#pragma once
#include <Arduino.h>

#include "DC2W.h"

namespace Car {
    namespace Buffer {
        class BufferDC2W {
        public:
            enum class COMMAND {
                RESET,
                GO,
                REVERSE,
                STIR
            };
        private:
            DigitalCar2W* car;
        public:
            BufferDC2W(DigitalCar2W& car);
            BufferDC2W(DigitalCar2W&& car);
            ~BufferDC2W();

            void begin() const;
        };        
    };
};