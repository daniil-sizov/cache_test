#ifndef CACHE_ENTRY_BASE_H
#define CACHE_ENTRY_BASE_H

struct CacheEntryBase
{
    CacheEntryBase(int tag, int index, int block_size, bool dirty = false);

    int tag;
    int index;
    int block_size;
    bool dirty;
};

#endif // CACHE_ENTRY_BASE_H