#pragma once
#include <Arduino.h>
#include "core.h"

namespace HTTP_Header {
    class ContentHeader : public core::BaseHeader {
        String content_type;
        String content_encoding;
        String content_md5;
        unsigned long int content_length = 0;
    public:

    };

    class ContentResponseHeader : public ContentHeader {
        String content_language;
        String content_location;
        String content_range;
    };
};