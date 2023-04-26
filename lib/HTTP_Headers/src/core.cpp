#include "core.h"

HTTP_Header::core::TrieNode::TrieNode() {
    table = new char*[1];
    *table = new char[26];
    memset(*table, -1, 26);
}

HTTP_Header::core::TrieNode::~TrieNode() {
    for(char** iter = table; iter != table + current; ++iter)
        delete[] (*iter);
    delete[] table;
}