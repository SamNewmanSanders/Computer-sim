#include "CircuitRenderer.h"

void CircuitRenderer::drawCircuit(std::vector<std::shared_ptr<Component>> subComponents, sf::RenderWindow& window)
{
    for(const auto& c : subComponents)
    {
        sf::Vector2f position = c->position;  // Reference to the unique_ptr

        // Remaking objects every frame is not performance critical as there aren't gonna be 1 million things in the cpu

        int numInputs = c->inputs.size();
        int numOutputs = c->currentOutputs.size();
        int maxPins = std::max(numInputs, numOutputs); // This corresponds to the component height

        float height = (maxPins - 1) * gridSize + gridSize; // + gridSize for padding
        float width = 2.f * gridSize;

        sf::RectangleShape compShape;    // Component shape

        compShape.setSize(sf::Vector2f(width, height));
        compShape.setFillColor(sf::Color(200, 200, 200));
        compShape.setOutlineColor(sf::Color::White);
        compShape.setOutlineThickness(2.f);
        compShape.setOrigin(sf::Vector2f(0.f, gridSize / 2.f)); // Set origin as top left pin
        compShape.setPosition(position);

        window.draw(compShape);


        // Setup input/output sockets
        float radius = gridSize / 4.f;

        for (size_t i = 0; i < numInputs; ++i)
        {
            sf::CircleShape pinShape;
            pinShape.setRadius(radius);
            pinShape.setOrigin(sf::Vector2f(radius, radius));
            pinShape.setFillColor(sf::Color::Red);

            float relY = i * gridSize;
            float relX = 0.0f;
            pinShape.setPosition(compShape.getPosition() + sf::Vector2f(relX, relY));
            window.draw(pinShape);
        }


        for (size_t i = 0; i < numOutputs; ++i)
        {
            sf::CircleShape pinShape;
            pinShape.setRadius(radius);
            pinShape.setOrigin(sf::Vector2f(radius, radius));
            pinShape.setFillColor(sf::Color::Green);

            float relY = i * gridSize;
            float relX = width;
            pinShape.setPosition(compShape.getPosition() + sf::Vector2f(relX, relY));
            window.draw(pinShape);
        }
    }
}


void CircuitRenderer::drawGrid(sf::RenderWindow& window, float bottomOffset)
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