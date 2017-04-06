#include "lru_cache_entry.h"

LRUCacheEntry::LRUCacheEntry(int tag, int index, int block_size, bool dirty)
    : CacheEntryBase(tag, index, block_size, dirty)
{
}