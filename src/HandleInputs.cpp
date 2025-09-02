#include "Simulation.h"

void Simulation::handleInputs()
{
    while (const std::optional event = window.pollEvent())
    {
        gui.handleEvent(*event);

        // Close window
        if (event->is<sf::Event::Closed>())
        {
            window.close();
            continue;
        }


        auto* kp = event->getIf<sf::Event::KeyPressed>();
        if (kp){
            if (kp->code == sf::Keyboard::Key::S)
            {
                simState.updateSim = true;
            }

            if (kp->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
        }

        if (auto* mm = event->getIf<sf::Event::MouseMoved>())
        {
            if (inputState.placingComponent)
            {
                // Snap to the grid
                float snappedPosX = static_cast<int>(mm->position.x / renderState.gridSize) * renderState.gridSize;
                float snappedPosY = static_cast<int>(mm->position.y  / renderState.gridSize) * renderState.gridSize;

                // NOTE - WHEN IT COMES TO MOVING EXISTING COMPONENTS AROUND THIS LAST ELEMENT IN VECTOR APPROACH WILL BREAK
                circuitBuilder.subComponents.back()->position = sf::Vector2f(snappedPosX, snappedPosY);
            }
        }

        // Mouse click → place component
        if (auto* mp = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mp->button == sf::Mouse::Button::Left && inputState.placingComponent)
            {
                inputState.placingComponent = false;
            }
        }

    }
}