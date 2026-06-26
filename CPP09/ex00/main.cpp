#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    Bitcoin btc;
    if (!btc.loadDB("data.csv")) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    if (!btc.run(argv[1])) {
        return 1;
    }

    return 0;
}
