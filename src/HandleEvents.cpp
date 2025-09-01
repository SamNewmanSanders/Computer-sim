#include "Simulation.h"

#include <memory>

void Simulation::handleEvents()
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
                updateSim = true;
            }

            if (kp->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
        }

        if (auto* mm = event->getIf<sf::Event::MouseMoved>())
        {
            if (placingVisualiser)
            {
                // Snap to the grid
                float snappedPosX = static_cast<int>(mm->position.x / gridSize) * gridSize;
                float snappedPosY = static_cast<int>(mm->position.y  / gridSize) * gridSize;

                placingVisualiser->setPosition(sf::Vector2f(snappedPosX, snappedPosY));
            }
        }

        // Mouse click → place component
        if (auto* mp = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mp->button == sf::Mouse::Button::Left && placingVisualiser)
            {
                components.push_back(placingVisualiser->component); // store the real component
                componentVisualisers.push_back(placingVisualiser);  // store visualiser (derefrence for the vector)

                placingVisualiser = nullptr;
            }
        }
    }
}