#ifndef CONSTANTS_H
#define CONSTANTS_H

enum WritePolicy {
    WRITE_THROUGH,
    WRITE_BACK
};

enum ReplacementPolicy {
    LRU,
    LFU,
    FIFO
};

enum CacheResult {
    MISS                    = 0x0,
    HIT                     = 0x1,
    CLEAN_REPLACED          = 0x10,
    DIRTY_REPLACED          = 0x11,
    NOTHING_REPLACED        = 0x100
};

const char * const CONFIG_PATH = "config.json";

#endif // CONSTANTS_H