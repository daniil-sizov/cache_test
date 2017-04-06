#include <exception>
#include "cache_base.h"
#include "lru_cache.h"
#include "fifo_cache.h"
#include "lfu_cache.h"

CacheBase::CacheBase(int cache_size, int block_size, int associativity)
    :   _cache_size(cache_size),
        _block_size(block_size),
        _associativity(associativity)
{
    if (_block_size < 1 || _associativity < 1 ||
        _cache_size % _block_size != 0 ||
        (_cache_size / _block_size) % _associativity != 0 ||
        _cache_size < 1)
    {
        throw std::logic_error("Invalid cache properties");
    }

    int acc = 0;
    while (cache_size > 0) {
        acc += cache_size & 1;
        cache_size /= 2;
    }
    while (block_size > 0) {
        acc += block_size & 1;
        block_size /= 2;
    }
    while (associativity > 0) {
        acc += associativity & 1;
        associativity /= 2;
    }
    if (acc != 3) {
        throw std::logic_error("Cache properties should be powers of 2");
    }
}

CacheBase::~CacheBase()
{
}

std::unique_ptr<CacheBase> CacheBase::create(ReplacementPolicy rp, int cs, int bs, int assoc) {
    switch (rp) {
    case ReplacementPolicy::FIFO:
        return std::unique_ptr<CacheBase>(new FIFOCache(cs, bs, assoc));
    case ReplacementPolicy::LFU:
        return std::unique_ptr<CacheBase>(new LFUCache(cs, bs, assoc));
    case ReplacementPolicy::LRU:
        return std::unique_ptr<CacheBase>(new LRUCache(cs, bs, assoc));
    }
    throw std::logic_error("Unknown replacement policy");
}