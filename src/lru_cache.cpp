#include <iterator>
#include <iostream>
#include "lru_cache.h"

LRUCache::LRUCache(int cs, int bs, int assoc)
    : CacheBase(cs, bs, assoc),
      _cache(cs / bs / assoc)
{
}

LRUCache::~LRUCache()
{
}

CacheResult LRUCache::read(int addr) {
    // std::cout << "cache size -> " << _cache.size() << ";  chunk sizes:";
    // for (auto &l : _cache) {
    //     std::cout << l.size() << " ";
    // }
    // std::cout << "\n";
    return _rw(addr);
}

CacheResult LRUCache::write(int addr) {
    return _rw(addr, true);
}

CacheResult LRUCache::place_entry(int addr, bool dirty) {
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
    _cache[ind].push_front(LRUCacheEntry(tag, ind, _block_size, dirty));

    return result;
}

CacheResult LRUCache::_rw(int addr, bool mark_dirty) {
    int tag = _get_tag(addr);
    int ind = _get_index(addr);
    auto e = _find_entry(tag, ind);
    if (e == _cache[ind].end()) {
        return CacheResult::MISS;
    }

    if (e != _cache[ind].begin()) {
        _cache[ind].splice(_cache[ind].begin(), _cache[ind], e, std::next(e));
    }

    if (mark_dirty) {
        e->dirty = true;
    }

    return CacheResult::HIT;
}

std::list<LRUCacheEntry>::iterator LRUCache::_find_entry(int tag, int ind) {

    for (auto i = _cache[ind].begin(); i != _cache[ind].end(); i++) {
        if (i->tag == tag) {
            return i;
        }
    }

    return _cache[ind].end();
}

int LRUCache::_get_index(int addr) const {
    int t = _cache_size / _block_size / _associativity;
    return (addr / _block_size) & (t - 1);
}

int LRUCache::_get_tag(int addr) const {
    return addr / _block_size / (_cache_size / _block_size / _associativity);
}
