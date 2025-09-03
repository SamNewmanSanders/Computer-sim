#include "CircuitBuilder.h"

void CircuitBuilder::addComponent(std::shared_ptr<Component> comp)
{
    subComponents.push_back(comp);
}

void CircuitBuilder::connect(std::shared_ptr<Pin> from, std::shared_ptr<Pin> to)
{
    from->connectedTo.push_back(to);
    to->connectedFrom = from;
}

std::shared_ptr<Circuit> CircuitBuilder::finalizeComponent()
{
    auto circuit = std::make_shared<Circuit>(subComponents, inputs, outputs);

    // Reset builder for reuse
    subComponents.clear();
    inputs.clear();
    outputs.clear();

    return circuit;
}

void CircuitBuilder::computeNextOutputs()
{
    for (auto& c : subComponents)
    {
        c->computeNextOutputs();
    }
}

void CircuitBuilder::updateOutputs() 
{
    for (auto& c : subComponents)
    {
        c->updateOutputs();
    }
}