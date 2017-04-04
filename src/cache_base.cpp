#include "cache_base.h"

CacheBase::CacheBase(int cache_size, int block_size, int associativity)
    :   _cache_size(cache_size),
        _block_size(block_size),
        _associativity(associativity)
{
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
}