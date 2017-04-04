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

    int mem_size;
    int cache_size;
    int block_size;
    int associativity;
    int hit_time;
    int access_time;
    WritePolicy write_policy;
    ReplacementPolicy replacement_policy;
};

#endif // SETTINGS_H