#include <iterator>
#include "fifo_cache.h"

FIFOCache::FIFOCache(int cs, int bs, int assoc)
    : CacheBase(cs, bs, assoc),
      _cache(cs / bs / assoc)
{
}

FIFOCache::~FIFOCache()
{
}

CacheResult FIFOCache::read(int addr) {
    return _rw(addr);
}

CacheResult FIFOCache::write(int addr) {
    return _rw(addr, true);
}

CacheResult FIFOCache::place_entry(int addr, bool dirty) {
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
    _cache[ind].push_front(FIFOCacheEntry(tag, ind, _block_size, dirty));

    return result;
}

CacheResult FIFOCache::_rw(int addr, bool mark_dirty) {
    int tag = _get_tag(addr);
    int ind = _get_index(addr);
    auto e = _find_entry(tag, ind);
    if (e == _cache[ind].end()) {
        return CacheResult::MISS;
    }

    if (mark_dirty) {
        e->dirty = true;
    }

    return CacheResult::HIT;
}

std::list<FIFOCacheEntry>::iterator FIFOCache::_find_entry(int tag, int ind) {

    for (auto i = _cache[ind].begin(); i != _cache[ind].end(); i++) {
        if (i->tag == tag) {
            return i;
        }
    }

    return _cache[ind].end();
}

int FIFOCache::_get_index(int addr) const {
    int t = _cache_size / _block_size / _associativity;
    return (addr / _block_size) & (t - 1);
}

int FIFOCache::_get_tag(int addr) const {
    return addr / _block_size / (_cache_size / _block_size / _associativity);
}
