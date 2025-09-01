#include <iostream>

#include "Simulation.h"

int main()
{
    Simulation sim;
    sim.run();
    std::cout << "Simulation exited succesfully." << std::endl;
    return 0;
}