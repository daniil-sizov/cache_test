#ifndef CPU_H
#define CPU_H

#include <memory>
#include "cache_base.h"
#include "constants.h"
#include "settings.h"
#include "statistics.h"

class Cpu
{
public:
    Cpu(const Settings &s);
    ~Cpu();

    void read(int addr);
    void write(int addr);

    const Statistics & get_stats() const;

private:
    std::unique_ptr<CacheBase> _cache;
    WritePolicy _write_policy;

    Statistics _stats;
};

#endif // CPU_H