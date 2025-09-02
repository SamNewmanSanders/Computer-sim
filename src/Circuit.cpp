#include "Circuit.h"

Circuit::Circuit(std::vector<std::shared_ptr<Component>> subComponents,
                std::vector<std::shared_ptr<Pin>> inputPins, 
                std::vector<std::shared_ptr<Pin>> outputPins)
                : subComponents(subComponents)
{
    // USE STD::MOVE? LEARN ABOUT THAT MAYBE LATER

    inputs = inputPins;  // Set base class variables (don't want another component constructor)
    currentOutputs = outputPins;
    nextOutputs.resize(currentOutputs.size(), false); // Also set up nextOutputs
}

void Circuit::computeNextOutputs()
{
    for (auto& c : subComponents)
    {
        c->computeNextOutputs();
    }
}
