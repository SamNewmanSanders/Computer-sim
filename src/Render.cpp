#include "Simulation.h"

#include <cmath>

void Simulation::render()
{
    drawGrid();

    for (auto& c : circuitBuilder.subComponents)
    {
      drawComponent(c);
    }
    
    if (inputState.ghostComponent) drawComponent(inputState.ghostComponent, true);

    if (inputState.drawingWire) drawWire(inputState.drawingWire);

    for (auto& w : renderState.wires) drawWire(w);
}

void Simulation::drawGrid()
{
    sf::Vector2u windowSize = window.getSize();
    sf::Color gridColor(200, 200, 200, 100); // Light gray with some transparency
    
    // Vertical lines
    for (float x = 0; x <= windowSize.x; x += renderState.gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, 0.f), gridColor),
            sf::Vertex(sf::Vector2f(x, static_cast<float>(windowSize.y - renderState.bottomOffset)), gridColor)
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Horizontal lines
    for (float y = 0.f; y <= (windowSize.y - renderState.bottomOffset); y += renderState.gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, y), gridColor),
            sf::Vertex(sf::Vector2f(static_cast<float>(windowSize.x), y), gridColor)
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}


void Simulation::drawComponent(const std::shared_ptr<Component>& c, bool isGhost)
{
    sf::Vector2f position = c->position;

    int numInputs = c->inputs.size();
    int numOutputs = c->currentOutputs.size();
    int maxPins = std::max(numInputs, numOutputs);

    float padding = renderState.gridSize * 0.3;
    float height = (maxPins - 1) * renderState.gridSize + padding * 2;
    float width  = 2.f * renderState.gridSize;

    sf::RectangleShape compShape;
    compShape.setSize(sf::Vector2f(width, height));
    compShape.setOutlineColor(sf::Color::White);
    compShape.setOutlineThickness(2.f);
    compShape.setOrigin(sf::Vector2f(0.f, padding));
    compShape.setPosition(position);

    // Different fill for ghost vs real
    compShape.setFillColor(isGhost ? sf::Color(200, 200, 200, 128)   // semi-transparent
                                   : sf::Color(200, 200, 200));

    window.draw(compShape);

    // Pins
    float radius = renderState.gridSize / 4.f;

    for (size_t i = 0; i < numInputs; ++i)
    {
        auto& p = c->inputs[i];

        sf::CircleShape pinShape(radius);
        pinShape.setOrigin(sf::Vector2f(radius, radius));
        sf::Color pinColor;
        if (p->highlighted)
            pinColor = sf::Color::Yellow;
        else
            pinColor = p->value ? sf::Color::Green : sf::Color::Red;
        pinShape.setFillColor(pinColor);


        float relY = i * renderState.gridSize;
        float relX = 0.0f;
        sf::Vector2f globalPos = compShape.getPosition() + sf::Vector2f(relX, relY);
        pinShape.setPosition(globalPos);
        window.draw(pinShape);

        if (!isGhost) // don’t update ghost pin positions permanently
            p->position = globalPos;
    }

    for (size_t i = 0; i < numOutputs; ++i)
    {
        
        auto& p = c->currentOutputs[i];

        sf::CircleShape pinShape(radius);
        pinShape.setOrigin(sf::Vector2f(radius, radius));
        sf::Color pinColor;
        if (p->highlighted)
            pinColor = sf::Color::Yellow;
        else
            pinColor = p->value ? sf::Color::Green : sf::Color::Red;
        pinShape.setFillColor(pinColor);


        float relY = i * renderState.gridSize;
        float relX = width;
        sf::Vector2f globalPos = compShape.getPosition() + sf::Vector2f(relX, relY);
        pinShape.setPosition(globalPos);
        window.draw(pinShape);

        if (!isGhost)
            p->position = globalPos;
    }
}


// CHATGPT IMPLEMENTED HAVE NOT CHECKED
void Simulation::drawWire(std::shared_ptr<Wire>& wire, float thickness)
{
    sf::Vector2f start = wire->startPin->position;
    //sf::Vector2f end = wire->endPin? wire->endPin->position : wire->tempEndPosition;
    sf::Vector2f end = wire->tempEndPosition;

    // Compute the vector from start to end
    sf::Vector2f delta = end - start;
    float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    // Create a rectangle with the correct length and thickness
    sf::RectangleShape wireShape(sf::Vector2f(length, thickness));
    wireShape.setFillColor(sf::Color::Yellow); // or any color you like

    // Set origin to left-center so rotation works naturally
    wireShape.setOrigin(sf::Vector2f(0.f, thickness / 2.f));
    wireShape.setPosition(start);

    // Compute angle in degrees
    float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;
    wireShape.setRotation(sf::radians(std::atan2(delta.y, delta.x)));

    // Draw the wire
    window.draw(wireShape);
}