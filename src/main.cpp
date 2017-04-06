#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <unistd.h>
#include "cpu.h"
#include "settings.h"
#include "constants.h"

void print_stats(const Statistics &s, const Settings &opts, bool extra) {
    // std::cout << s.cache_writes << std::endl;
    // std::cout << s.cache_reads << std::endl;
    // std::cout << s.memory_writes << std::endl;
    // std::cout << s.memory_reads << std::endl;
    // std::cout << s.cache_hits << std::endl;
    // std::cout << s.cache_misses << std::endl;
    // std::cout << static_cast<double>(s.cache_hits) / (s.cache_hits + s.cache_misses) << std::endl;
    double MS = opts.mem_size / 1024.0 / 1024;
    double CS = opts.cache_size / 1024.0;
    int BS = opts.block_size;
    int A = opts.associativity;
    int HT = opts.hit_time;
    int AT = opts.access_time;
    std::string WP = opts.write_policy == WritePolicy::WRITE_BACK ? "WB" : "WT";
    std::string RP = opts.replacement_policy == ReplacementPolicy::FIFO ? "FIFO" :
        opts.replacement_policy == ReplacementPolicy::LFU ? "LFU" : "LRU";
    double HR = static_cast<double>(s.cache_hits) / (s.cache_hits + s.cache_misses);
    double AMAT = static_cast<double>((s.cache_reads + s.cache_writes) * HT +
                   (s.memory_reads + s.memory_writes) * AT) / (s.cache_reads + s.writes);
    
    std::ostringstream out;
    out.precision(1);
    out << std::fixed << MS;
    std::cout << std::left << std::setw(9) << out.str() + "MB";
    
    out.str("");
    out << CS;
    std::cout << std::setw(9) << out.str() + "KB";

    std::cout << std::setw(8) << BS;
    
    std::cout << std::setw(4) << A;

    std::cout << std::setw(12) << std::to_string(HT) + "/" + std::to_string(AT) + "ns";

    std::cout << std::setw(8) << WP;
    
    std::cout << std::setw(8) << RP;

    std::cout << std::setprecision(2) << std::setw(8) << HR;
    std::cout << std::setprecision(1) << std::fixed << AMAT << "ns  ";

    if (extra) {
        std::cout << std::setw(8) << s.cache_reads;
        // std::cout << std::setw(8) << s.cache_reads;
        std::cout << std::setw(8) << s.memory_reads;
        std::cout << std::setw(8) << s.writes;
        // std::cout << std::setw(8) << s.cache_writes;
        std::cout << std::setw(8) << s.memory_writes;
    }

    std::cout << "\n";
}

void print_usage() {
    std::cout << "\n";
    std::cout << "USAGE\n";
    std::cout << "\t"<< "cache_test [OPTIONS] TEST_SEQUENCE_FILE\n";
    std::cout << "\n";
    std::cout << "OPTIONS\n";
    std::cout << "\t" << "-h,    show help" << "\n";
    std::cout << "\t" << "-v,    show extra statistics" << "\n";
    std::cout << "\t" << "-l,    show legend and table header" << "\n";
    std::cout << "\t" << "-m,    set memory size (in bytes)" << "\n";
    std::cout << "\t" << "-c,    set cache size (in bytes)" << "\n";
    std::cout << "\t" << "-b,    set block size (in bytes)" << "\n";
    std::cout << "\t" << "-a,    set associativity" << "\n";
    std::cout << "\t" << "-i,    set cache access time (in ns)" << "\n";
    std::cout << "\t" << "-s,    set memory access time (in ns)" << "\n";
    std::cout << "\t" << "-w,    set writing policy (write-through or write-back)" << "\n";
    std::cout << "\t" << "-r,    set replacement policy (LRU, LFU or FIFO)" << "\n";
    std::cout << "\n";
}

void print_legend(bool extra) {
    std::cout << "" << "\n";
    std::cout << "    MS     -- memory size" << "\n";
    std::cout << "    CS     -- cache size" << "\n";
    std::cout << "    BS     -- block size" << "\n";
    std::cout << "    A      -- cache associativity" << "\n";
    std::cout << "    HT/AT  -- cache hit (access) time / memory access time" << "\n";
    std::cout << "    WP     -- cache writing policy (write-trough [WT] / write-back [WB]" << "\n";
    std::cout << "    RP     -- cache replacement policy (LRU / LFU / FIFO)" << "\n";
    std::cout << "    HR     -- hit rate (* - only on reads for write-through)" << "\n";
    std::cout << "    AMAT   -- average memory access time (including writes)" << "\n";

    if (extra) {
        std::cout << "    READS  -- total read operations in test sequence" << "\n";
//        std::cout << "    CR     -- cache accesses to read" << "\n";
        std::cout << "    MR     -- memory accesses to read" << "\n";
        std::cout << "    WRITES -- total write operations in test sequence" << "\n";
//        std::cout << "    CW     -- cache accesses to write" << "\n";
        std::cout << "    MW     -- memory accesses to write" << "\n";
    }
    std::cout << "" << "\n";
    std::cout << "  MS      CS      BS      A       HT/AT   WP      RP      HR      AMAT  ";

    if (extra) {
        std::cout << "    READS   MR     WRITES   MW\n";
        std::cout << "------------------------------";
    } else {
        std::cout << "\n";
    }
    std::cout << "-------------------------------------------------------------------------";

    std::cout << "\n";
}

int main(int argc, char **argv) {
    std::ifstream cfg_file(CONFIG_PATH);

    if (!cfg_file.is_open()) {
        std::cerr << "Configuration file is not found\n";
        return 1;
    }

    Settings settings(cfg_file);

    bool extra = false;
    bool legend = false;
    int opt = 0;
    opterr = 0;
    std::string tmp;
    while ( (opt = getopt(argc, argv, "m:c:b:a:i:s:w:r:lvh")) != -1 ) { 
        switch ( opt ) {
        case 'm':
            settings.mem_size = std::stoi(optarg);
            break;
        case 'c':
            settings.cache_size = std::stoi(optarg);
            break;
        case 'b':
            settings.block_size = std::stoi(optarg);
            break;
        case 'a':
            settings.associativity = std::stoi(optarg);
            break;
        case 'i':
            settings.hit_time = std::stoi(optarg);
            break;
        case 's':
            settings.access_time = std::stoi(optarg);
            break;
        case 'w':
            tmp = optarg;
            if (tmp == "write-through") {
                settings.write_policy = WritePolicy::WRITE_THROUGH;
            } else if (tmp == "write-back") {
                settings.write_policy = WritePolicy::WRITE_BACK;
            } else {
                std::cerr << "Unknown write policy\n";
                return 1;
            }
            break;
        case 'r':
            tmp = optarg;
            if (tmp == "LRU") {
                settings.replacement_policy = ReplacementPolicy::LRU;
            } else if (tmp == "LFU") {
                settings.replacement_policy = ReplacementPolicy::LFU;
            } else if (tmp == "FIFO") {
                settings.replacement_policy = ReplacementPolicy::FIFO;
            } else {
                std::cerr << "Unknown replacement policy\n";
                return 1;
            }
            break;
        case 'l':
            legend = true;
            break;
        case 'v':
            extra = true;
            break;
        case 'h':
            print_usage();
            return 0;
        case '?':
            std::cerr << "Unknown option: '" << char(optopt) << "'!\n";
            break;
        }
    }

    if (legend) { 
        print_legend(extra);
    }

    if (optind >= argc) {
        print_usage();
    }

    std::ifstream test_seq(argv[optind]);
    if (!test_seq.is_open()) {
        std::cerr << "Test sequence file is not found\n";
        return 1;
    }

    int mem_size = settings.mem_size;
    if (mem_size <= 0) {
        std::cerr << "Memory size is invalid\n";
        return 1;
    }

    Cpu cpu(settings);

    std::string op;
    unsigned int addr;
    while (test_seq >> op) {
        test_seq >> std::hex >> addr;
        addr %= settings.mem_size;

        if (op == "R") {
            cpu.read(addr);
        } else if (op == "W") {
            cpu.write(addr);
        }
    }

    print_stats(cpu.get_stats(), settings, extra);

    return 0;
}