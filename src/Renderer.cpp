#include "Renderer.h"

void Renderer::drawGrid(sf::RenderWindow& window, float bottomOffset)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Color gridColor(200, 200, 200, 100); // Light gray with some transparency
    
    // Vertical lines
    for (float x = 0; x <= windowSize.x; x += gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, 0.f), gridColor),
            sf::Vertex(sf::Vector2f(x, static_cast<float>(windowSize.y - bottomOffset)), gridColor)
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Horizontal lines
    for (float y = 0.f; y <= (windowSize.y - bottomOffset); y += gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, y), gridColor),
            sf::Vertex(sf::Vector2f(static_cast<float>(windowSize.x), y), gridColor)
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}


void Renderer::drawComponents(sf::RenderWindow& window, const std::vector<std::shared_ptr<ComponentVisualiser>>& visualisers)
{
    for (const auto& visualiser : visualisers)
    {
        visualiser->draw(window);
    }
}
