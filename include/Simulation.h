#pragma once

#include <SFML/Graphics.hpp>  // SFML 3
#include <SFML/Window.hpp> 
#include <SFML/System.hpp> 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <vector>

#include "Circuit.h"
#include "CircuitBuilder.h"
#include "Wire.h"


class Simulation
{
public:
    Simulation();

    void run();
    void render();

private:

    // Input helpers
    void handleInputs();
    void setupButtons();
    bool isMouseOverPoint(const sf::Vector2f& mousePos, const sf::Vector2f& thingPos, float halfSize);
    bool isMouseOverBox(const sf::Vector2f& mousePos, const sf::Vector2f& pos, const sf::Vector2f& size);

    // Render helpers
    void drawGrid();
    void drawComponent(const std::shared_ptr<Component>& c, bool isGhost = false);
    void drawWire(std::shared_ptr<Wire>& wire, float thickness = 4.f);

    sf::RenderWindow window;
    tgui::Gui gui;

    CircuitBuilder circuitBuilder;

    // std::shared_ptr<Circuit> mainCircuit = nullptr; // DONT EVEN HAVE THIS AS A VARIABLE ANYMORE, ALL YOULL EVER *SEE* IS THE BUILDER

    struct SimState
    {
        bool updateSim = false;
    };
    SimState simState;

    struct InputState
    {
        std::shared_ptr<Component> ghostComponent = nullptr;  // This is the component that is being currently placed. Also acts like a bool
        std::shared_ptr<Wire> drawingWire; // Similarly use this as a bool
        std::shared_ptr<Pin> highlightedInputPin = nullptr;
        std::shared_ptr<Pin> highlightedOutputPin = nullptr;
        std::shared_ptr<Component> selectedInputComponent = nullptr;    // This is to help with changing the state of input pins
    };
    InputState inputState;

    struct RenderState
    {
        float gridSize;
        float bottomOffset;
        std::vector<std::shared_ptr<Wire>> wires;    // Placed them here as they are just for drawing
    };
    RenderState renderState;
};