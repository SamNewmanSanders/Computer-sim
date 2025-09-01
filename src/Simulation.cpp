#include "Simulation.h"

Simulation::Simulation()
    : window(
        sf::VideoMode::getDesktopMode(),  // fullscreen uses the current desktop resolution
        "CPU Simulation",
        sf::Style::Default,
        sf::State::Fullscreen),
    renderer(gridSize)
{
    window.setKeyRepeatEnabled(false);
    gui.setTarget(window);

    //setupDemoCircuit();

    setupButtons();
}

void Simulation::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}


void Simulation::update()
{
    if (!updateSim) return;

    for (auto& c : components) c->computeNextOutputs();
    for (auto& c : components) c->updateOutputs();
    updateSim = false;
}

void Simulation::render()
{
    window.clear(sf::Color::Black);
    renderer.drawGrid(window, 60.0f); // leave room for buttons
    renderer.drawComponents(window, componentVisualisers);

    if (placingVisualiser)
    {
        placingVisualiser->shape.setFillColor(sf::Color(255, 255, 255, 150)); // slightly transparent
        window.draw(placingVisualiser->shape);
    }

    gui.draw();
    window.display();
}



