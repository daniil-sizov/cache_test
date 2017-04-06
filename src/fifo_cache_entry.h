#ifndef FIFO_CACHE_ENTRY_H
#define FIFO_CACHE_ENTRY_H

#include "cache_entry_base.h"

struct FIFOCacheEntry : public CacheEntryBase
{
    FIFOCacheEntry(int tag, int index, int block_size, bool dirty = false);
};

#endif // FIFO_CACHE_ENTRY_H