#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Circuit.h"
#include "CircuitBuilder.h"

class CircuitRenderer
{

public:

    CircuitRenderer(float gridSize) : gridSize(gridSize) {}

    void drawCircuit(std::vector<std::shared_ptr<Component>> subComponents, sf::RenderWindow& window); 
    // Note "drawCircuit" will draw its sub components. E.G drawCPU will draw whats inside the cpu, not the cpu black box

    void drawGrid(sf::RenderWindow& window, float bottomOffset);

private:

    float gridSize;

};