#include "statistics.h"

Statistics::Statistics()
    : cache_writes(0),
      cache_reads(0),
      memory_writes(0),
      memory_reads(0),
      cache_hits(0),
      cache_misses(0)
{
}