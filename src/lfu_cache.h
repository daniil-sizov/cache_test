#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <vector>
#include <list>
#include "cache_base.h"
#include "lfu_cache_entry.h"

class LFUCache : public CacheBase
{
public:
    LFUCache(int cs, int bs, int assoc);
    ~LFUCache();

    CacheResult read(int addr) override;
    CacheResult write(int addr) override;
    CacheResult place_entry(int addr, bool dirty = false) override;

private:
    std::vector<std::list<LFUCacheEntry>> _cache;

    std::list<LFUCacheEntry>::iterator _find_entry(int tag, int ind);
    int _get_tag(int addr) const;
    int _get_index(int addr) const;
    CacheResult _rw(int addr, bool mark_dirty = false);
};

#endif // LFU_CACHE_H