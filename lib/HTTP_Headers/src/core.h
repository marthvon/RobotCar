#pragma once
#include <Arduino.h>

namespace HTTP_Header {
namespace core {
    class BaseHeader {

    public:

    };
    struct stringToIntPair {
        String s;
        int i;
    };
    class TrieNode {
        char** table;
        size_t capacity = 1;
        size_t current_index = 0;
        size_t current = 0;
        int* index;
    public:
        constexpr TrieNode();
        constexpr TrieNode(stringToIntPair* list);
        ~TrieNode();
    };
};
};
