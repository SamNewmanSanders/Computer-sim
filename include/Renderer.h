#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "ComponentVisualiser.h"

class Renderer {
public:
    Renderer(float gridSize) : gridSize(gridSize) {}

    void drawGrid(sf::RenderWindow& window, float bottomOffset = 0.f);
    void drawComponents(sf::RenderWindow& window, const std::vector<std::shared_ptr<ComponentVisualiser>>& visualisers);

private:
    float gridSize;
};
