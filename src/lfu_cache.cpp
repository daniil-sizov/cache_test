#include <iterator>
#include "lfu_cache.h"

LFUCache::LFUCache(int cs, int bs, int assoc)
    : CacheBase(cs, bs, assoc),
      _cache(cs / bs / assoc)
{
}

LFUCache::~LFUCache()
{
}

CacheResult LFUCache::read(int addr) {
    return _rw(addr);
}

CacheResult LFUCache::write(int addr) {
    return _rw(addr, true);
}

CacheResult LFUCache::place_entry(int addr, bool dirty) {
    CacheResult result = CacheResult::NOTHING_REPLACED;
    int tag = _get_tag(addr);
    int ind = _get_index(addr);

    if (_cache[ind].size() == static_cast<size_t>(_associativity)) {
        if (_cache[ind].back().dirty) {
            result = CacheResult::DIRTY_REPLACED;
        } else {
            result = CacheResult::CLEAN_REPLACED;
        }
        _cache[ind].pop_back();
    }
    _cache[ind].push_front(LFUCacheEntry(tag, ind, _block_size, dirty));

    return result;
}

CacheResult LFUCache::_rw(int addr, bool mark_dirty) {
    int tag = _get_tag(addr);
    int ind = _get_index(addr);
    auto e = _find_entry(tag, ind);
    if (e == _cache[ind].end()) {
        return CacheResult::MISS;
    }

    e->freq++;
    while (e != _cache[ind].begin() && std::prev(e)->freq > e->freq) {
        std::swap(*e, *std::prev(e));
        e--;
    }

    if (mark_dirty) {
        e->dirty = true;
    }

    return CacheResult::HIT;
}

std::list<LFUCacheEntry>::iterator LFUCache::_find_entry(int tag, int ind) {

    for (auto i = _cache[ind].begin(); i != _cache[ind].end(); i++) {
        if (i->tag == tag) {
            return i;
        }
    }

    return _cache[ind].end();
}

int LFUCache::_get_index(int addr) const {
    int t = _cache_size / _block_size / _associativity;
    return (addr / _block_size) & (t - 1);
}

int LFUCache::_get_tag(int addr) const {
    return addr / _block_size / (_cache_size / _block_size / _associativity);
}
