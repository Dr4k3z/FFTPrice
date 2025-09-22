#include <iostream>
#include "GBMSimulation.h"
#include <chrono>

int main() {
    GBMParameters par(100,0.2,0.1,1,1000,1000,42);
    GBMSimulation sim(par);

    std::cout << "starting simulation...\n";

    auto start = std::chrono::system_clock::now();
    sim.simulate();
    auto end = std::chrono::system_clock::now();

    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start) << "\n";

    return 0;
}