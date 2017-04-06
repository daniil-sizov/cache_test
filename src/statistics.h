#ifndef STATISTICS_H
#define STATISTICS_H

struct Statistics
{
    Statistics();

    int cache_writes;
    int cache_reads;
    int memory_writes;
    int memory_reads;
    int cache_hits;
    int cache_misses;
    int writes;
};

#endif // STATISTICS_H