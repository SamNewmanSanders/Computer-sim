#include "Simulation.h"

Simulation::Simulation()
    :   //window(sf::VideoMode::getDesktopMode(), "CPU Simulation",sf::Style::Default,sf::State::Fullscreen),
        window(sf::VideoMode({800, 600}), "My window"),
        circuitRenderer(40.0f) // Set gridsize
    
{
    window.setKeyRepeatEnabled(false);
    gui.setTarget(window);
    setupButtons();

    renderState.gridSize = 40.0f;
}

void Simulation::run()
{
    while (window.isOpen())
    {
        handleInputs();

        if (simState.updateSim)
        {
            mainCircuit->computeNextOutputs();
            mainCircuit->updateOutputs();
            simState.updateSim = false;
        }

        window.clear();
        circuitRenderer.drawGrid(window, 40.0f);

        circuitRenderer.drawCircuit(circuitBuilder.subComponents, window);  
        if (mainCircuit) circuitRenderer.drawCircuit(mainCircuit->subComponents, window);

        gui.draw();
        window.display();
    }
}


