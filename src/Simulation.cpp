#include "Simulation.h"

Simulation::Simulation()
    :   //window(sf::VideoMode::getDesktopMode(), "CPU Simulation",sf::Style::Default,sf::State::Fullscreen)
        window(sf::VideoMode({1000, 800}), "My window")
    
{
    window.setKeyRepeatEnabled(false);
    gui.setTarget(window);
    setupButtons();

    // Set visual variables
    renderState.gridSize = 30.0f;
    renderState.bottomOffset = 80.0f;
}

void Simulation::run()
{
    while (window.isOpen())
    {
        handleInputs();

        if (simState.updateSim)
        {
            // REPLACE THIS WITH CIRCUT BUILDER LOGIC I AM YET TO IMPLEMENT
            // mainCircuit->computeNextOutputs();
            // mainCircuit->updateOutputs();
            simState.updateSim = false;
        }

        window.clear();
        
        render();

        gui.draw();
        window.display();
    }
}


