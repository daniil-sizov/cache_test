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

const char * const CONFIG_PATH = "config.json";

#endif // CONSTANTS_H