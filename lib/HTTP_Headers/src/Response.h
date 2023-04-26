#pragma once
#include <Arduino.h>
#include "General.h"
#include "Content.h"
#include "core.h"

namespace HTTP_Header {
    class ResponseHeader : public core::GeneralHeader {
        unsigned short int response_code;
    public:
    
    };
};