#ifndef LRU_CACHE_ENTRY_H
#define LRU_CACHE_ENTRY_H

#include "cache_entry_base.h"

struct LRUCacheEntry : public CacheEntryBase
{
    LRUCacheEntry(int tag, int index, int block_size, bool dirty = false);
};

#endif // LRU_CACHE_ENTRY_H