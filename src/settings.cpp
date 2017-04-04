#include <exception>
#include "settings.h"
#include "constants.h"

Settings::Settings() {}

Settings::Settings(std::istream &in) {
    json cfg;
    in >> cfg;

    try
    {
        mem_size = cfg["mem_size"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read mem_size from configuration stream\n";
        throw e;
    }

    try
    {
        cache_size = cfg["cache_size"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read cache_size from configuration stream\n";
        throw e;
    }

    try
    {
        block_size = cfg["block_size"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read block_size from configuration stream\n";
        throw e;
    }

    try
    {
        associativity = cfg["associativity"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read associativity from configuration stream\n";
        throw e;
    }

    try
    {
        hit_time = cfg["hit_time"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read hit_time from configuration stream\n";
        throw e;
    }

    try
    {
        access_time = cfg["access_time"];
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read access_time from configuration stream\n";
        throw e;
    }

    try
    {
        std::string wp = cfg["write_policy"];
        if (wp == "write-through") {
            write_policy = WritePolicy::WRITE_THROUGH;
        } else if (wp == "write-back") {
            write_policy = WritePolicy::WRITE_BACK;
        } else {
            throw std::logic_error("Unknown write policy");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read write_policy from configuration stream\n";
        throw e;
    }

    try
    {
        std::string rp = cfg["replacement_policy"];
        if (rp == "LRU") {
            replacement_policy = ReplacementPolicy::LRU;
        } else if (rp == "LFU") {
            replacement_policy = ReplacementPolicy::LFU;
        } else if (rp == "FIFO") {
            replacement_policy = ReplacementPolicy::FIFO;
        } else {
            throw std::logic_error("Unknown replacement policy");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to read replacement_policy from configuration stream\n";
        throw e;
    }
}