#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <string>
#include "constants.h"
#include "lib/json.hpp"

using json = nlohmann::json;

struct Settings
{
    Settings();
    Settings(std::istream &in);

    // memory size in bytes
    int mem_size;

    // cache size in bytes
    int cache_size;

    // cache block size in bytes
    int block_size;

    // cache associativity
    int associativity;

    // time to access data in cache
    int hit_time;

    // time to access data in memory
    int access_time;

    // write policy, can be write-back or write-through
    WritePolicy write_policy;

    // replacement policy, can be LFU, LRU or FIFO
    ReplacementPolicy replacement_policy;
};

#endif // SETTINGS_H