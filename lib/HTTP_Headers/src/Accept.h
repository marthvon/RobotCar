#pragma once
#include "Arduino.h"
#include "core.h"

namespace HTTP_Header { 
namespace Request {
    class AcceptHeader : public core::BaseHeader {
        String accept;
        String accept_language;
        String accept_charset;
        String accept_language;
    public:

    };
}; 
};