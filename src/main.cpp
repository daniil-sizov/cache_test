#include <iostream>
#include <fstream>
#include <vector>
#include "settings.h"
#include "constants.h"

int main(int argс, char **argv) {
    std::ifstream cfg_file(CONFIG_PATH);

    if (!cfg_file.is_open()) {
        std::cerr << "Configuration file is not found\n";
        return 1;
    }

    Settings settings(cfg_file);

    return 0;
}