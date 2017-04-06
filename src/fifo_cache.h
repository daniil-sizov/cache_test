#ifndef FIFO_CACHE_H
#define FIFO_CACHE_H

#include <vector>
#include <list>
#include "cache_base.h"
#include "fifo_cache_entry.h"

class FIFOCache : public CacheBase
{
public:
    FIFOCache(int cs, int bs, int assoc);
    ~FIFOCache();

    CacheResult read(int addr) override;
    CacheResult write(int addr) override;
    CacheResult place_entry(int addr, bool dirty = false) override;

private:
    std::vector<std::list<FIFOCacheEntry>> _cache;

    std::list<FIFOCacheEntry>::iterator _find_entry(int tag, int ind);
    int _get_tag(int addr) const;
    int _get_index(int addr) const;
    CacheResult _rw(int addr, bool mark_dirty = false);
};

#endif // FIFO_CACHE_H