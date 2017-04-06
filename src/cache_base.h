#ifndef CACHE_BASE_H
#define CACHE_BASE_H

#include <memory>
#include "constants.h"

class CacheBase
{
public:
    CacheBase(int cache_size, int block_size, int associativity);
    virtual ~CacheBase();

    virtual CacheResult read(int addr) = 0;
    virtual CacheResult write(int addr) = 0;
    virtual CacheResult place_entry(int addr, bool dirty = false) = 0;

    static std::unique_ptr<CacheBase> create(ReplacementPolicy rp, int cs, int bs, int assoc);

protected:
    int _cache_size;
    int _block_size;
    int _associativity;
};

#endif // CACHE_BASE_H