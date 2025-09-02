#pragma once

#include <SFML/Graphics.hpp>

#include "Components.h"

class Wire
{
public:

    void setStartPin(std::shared_ptr<Pin> start) {startPin = start;}
    void setEndPin(std::shared_ptr<Pin> end) {endPin = end;}

    void linkPins() // Maybe shouldn't be here but convenient to link pins when wire is finished
    {
        startPin->connectedTo.push_back(endPin);
        endPin->connectedFrom = startPin;
    }

    void unlinkPins() // NEED TO IMPLEMENT THIS IN A DESTRUCTOR OR CALL IT FROM ABOVE LATER WHEN I ADD UNDO SHIT
    {
        if (startPin) {
            // Remove this endPin from startPin->connectedTo
            auto& vec = startPin->connectedTo;
            vec.erase(std::remove(vec.begin(), vec.end(), endPin), vec.end());
        }

        if (endPin) {
            // Only clear if endPin->connectedFrom points to startPin
            if (endPin->connectedFrom == startPin) {
                endPin->connectedFrom = nullptr;
            }
        }
    }

    std::shared_ptr<Pin> startPin = nullptr;
    std::shared_ptr<Pin> endPin = nullptr;

    sf::Vector2f tempStartPosition;     // These should be used when drawing the wire when the pins aren't defined
    sf::Vector2f tempEndPosition;       // Note start position isn't neccesary yet as you always set that first atm
};