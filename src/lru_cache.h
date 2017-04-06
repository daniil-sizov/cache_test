#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <vector>
#include <list>
#include "cache_base.h"
#include "lru_cache_entry.h"

class LRUCache : public CacheBase
{
public:
    LRUCache(int cs, int bs, int assoc);
    ~LRUCache();

    CacheResult read(int addr) override;
    CacheResult write(int addr) override;
    CacheResult place_entry(int addr, bool dirty = false) override;

private:
    std::vector<std::list<LRUCacheEntry>> _cache;

    std::list<LRUCacheEntry>::iterator _find_entry(int tag, int ind);
    int _get_tag(int addr) const;
    int _get_index(int addr) const;
    CacheResult _rw(int addr, bool mark_dirty = false);
};

#endif // LRU_CACHE_H