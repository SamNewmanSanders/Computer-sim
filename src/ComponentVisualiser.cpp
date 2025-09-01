#include "ComponentVisualiser.h"

#include <iostream>

ComponentVisualiser::ComponentVisualiser(std::shared_ptr<Component> comp, float gridSize)
    : component(comp), gridSize(gridSize)
{
    numInputs = component->inputs.size();
    numOutputs = component->currentOutputs.size();
    maxPins = std::max(numInputs, numOutputs);

    float height = (maxPins - 1) * gridSize + gridSize; // + gridSize for padding
    width = 2.f * gridSize;

    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(200, 200, 200));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2.f);
    shape.setOrigin(sf::Vector2f(0.f, gridSize / 2.f)); // Set origin as top left pin

    // Setup input/output sockets
    float radius = gridSize / 4.f;
    ioPins.clear();

    for (size_t i = 0; i < numInputs; ++i)
        ioPins.emplace_back(true, i, radius, sf::Color::Red);

    for (size_t i = 0; i < numOutputs; ++i)
        ioPins.emplace_back(false, i, radius, sf::Color::Green);
}
