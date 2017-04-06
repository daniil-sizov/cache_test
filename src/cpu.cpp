#include "cpu.h"

Cpu::Cpu(const Settings &s)
    : _cache(CacheBase::create(s.replacement_policy, s.cache_size, s.block_size, s.associativity)),
      _write_policy(s.write_policy)
{
}

Cpu::~Cpu()
{
}

void Cpu::read(int addr) {
    CacheResult result = _cache->read(addr);

    if (result == CacheResult::MISS) {
        result = _cache->place_entry(addr);

        if (result == CacheResult::DIRTY_REPLACED) {
            _stats.memory_writes++;
        }
        _stats.cache_misses++;
        _stats.memory_reads++;
    } else {
        _stats.cache_hits++;
    }
    _stats.cache_reads++;
}

void Cpu::write(int addr) {
    _stats.writes++;
    if (_write_policy == WritePolicy::WRITE_THROUGH) {
        _stats.memory_writes++;
        return;
    }

    CacheResult result = _cache->write(addr);

    if (result == CacheResult::MISS) {
        result = _cache->place_entry(addr, true);

        if (result == CacheResult::DIRTY_REPLACED) {
            _stats.memory_writes++;
        }
        _stats.cache_misses++;
    } else {
        _stats.cache_hits++;
    }
    _stats.cache_writes++;
}

const Statistics & Cpu::get_stats() const {
    return _stats;
}