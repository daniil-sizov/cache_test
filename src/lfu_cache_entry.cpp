#include "lfu_cache_entry.h"

LFUCacheEntry::LFUCacheEntry(int tag, int index, int block_size, bool dirty)
    : CacheEntryBase(tag, index, block_size, dirty), freq(0)
{
}