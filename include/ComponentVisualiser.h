#pragma once

#include <SFML/Graphics.hpp>

#include "Components.h"

struct PinVisualiser
{
    sf::CircleShape shape;
    bool isInput;
    std::shared_ptr<Component> pinParent;

    PinVisualiser(bool input, size_t idx, float radius, sf::Color color, Component&, std::shared_ptr<Component> pinParent)
        : isInput(input), index(idx), pinParent(pinParent)
    {
        shape.setRadius(radius);
        shape.setOrigin(sf::Vector2f(radius, radius));
        shape.setFillColor(color);
    }

    bool contains(const sf::Vector2f& point) const
    {
        return shape.getGlobalBounds().contains(point);
    }
};

class ComponentVisualiser
{
public:
    std::shared_ptr<Component> component; // To retrieve the logic info

    float gridSize;   // Record these to make it easier update position
    size_t maxPins; 
    float width;
    size_t numInputs;
    size_t numOutputs;

    sf::RectangleShape shape;
    sf::Vector2f position;
    std::vector<PinVisualiser>  ioPins; // Represent the component pins (both input and output)
   

    ComponentVisualiser(std::shared_ptr<Component> component, float gridSize);

    void draw(sf::RenderWindow& window) const
    {
        window.draw(shape);

        for (auto& pv : ioPins){ 
            window.draw(pv.shape);
        }
    }

    void setPosition(const sf::Vector2f& pos)
    {
        position = pos;
        shape.setPosition(pos);

        float radius = gridSize / 4.f;

        for (size_t i = 0; i < ioPins.size(); ++i)
        {
            PinVisualiser& pin = ioPins[i];
            float relY = pin.index * gridSize;
            float relX = pin.isInput ? 0.f : width;
            pin.shape.setPosition(shape.getPosition() + sf::Vector2f(relX, relY));
        }
    }
};
