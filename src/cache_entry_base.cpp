#include "cache_entry_base.h"

CacheEntryBase::CacheEntryBase(int tag, int index, int block_size, bool dirty)
    : tag(tag), index(index), block_size(block_size), dirty(false)
{
}