#pragma once

#include <SFML/Graphics.hpp>  // SFML 3
#include <SFML/Window.hpp> 
#include <SFML/System.hpp> 
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <vector>

#include "Circuit.h"
#include "CircuitRenderer.h"
#include "CircuitBuilder.h"


class Simulation
{
public:
    Simulation();

    void run();

private:

    // Helper files
    void handleInputs();
    void setupButtons();

    sf::RenderWindow window;
    tgui::Gui gui;

    CircuitBuilder circuitBuilder;
    CircuitRenderer circuitRenderer;

    std::shared_ptr<Circuit> mainCircuit = nullptr; // Null until it is finalized


    struct SimState
    {
        bool updateSim = false;
    };

    SimState simState;

    struct InputState
    {
        bool placingComponent = false;
    };

    InputState inputState;

    struct RenderState
    {
        float gridSize;
    };

    RenderState renderState;

};