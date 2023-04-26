#pragma once
#include <Arduino.h>
#include "core.h"

namespace HTTP_Header {
namespace core {
    class GeneralHeader {

        String connection;
        String upgrade;
        String date;

        core::BaseHeader* list_of_headers;
    };
};
};
