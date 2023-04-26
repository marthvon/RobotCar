#pragma once
#include <Arduino.h>
#include "General.h"
#include "core.h"

namespace HTTP_Header {
    class RequestHeader : public core::GeneralHeader {
        enum class METHOD {
            GET,
            POST,
            PUT,
            PATCH,
            DELETE,
            HEAD
        } method;

        String host;
        String x_requested_with;
        bool upgrade_insecure_request;
        bool DNT;
    public:

    };
};