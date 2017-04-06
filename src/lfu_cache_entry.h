#ifndef LFU_CACHE_ENTRY_H
#define LFU_CACHE_ENTRY_H

#include "cache_entry_base.h"

struct LFUCacheEntry : public CacheEntryBase
{
    LFUCacheEntry(int tag, int index, int block_size, bool dirty = false);

    int freq;
};

#endif // LFU_CACHE_ENTRY_H