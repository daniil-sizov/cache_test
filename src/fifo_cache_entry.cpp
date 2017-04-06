#include "fifo_cache_entry.h"

FIFOCacheEntry::FIFOCacheEntry(int tag, int index, int block_size, bool dirty)
    : CacheEntryBase(tag, index, block_size, dirty)
{
}