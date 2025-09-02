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
            if (inputState.ghostComponent)  // Checks if not null
            {
                // Snap to the grid
                float snappedPosX = static_cast<int>(mm->position.x / renderState.gridSize) * renderState.gridSize;
                float snappedPosY = static_cast<int>(mm->position.y  / renderState.gridSize) * renderState.gridSize;

                inputState.ghostComponent->position = sf::Vector2f(snappedPosX, snappedPosY);
                return; // THIS MIGHT CAUSE ISSUES WHERE EVENTS ARE MISSED IN THE FUTURE I'M NOT SURE
            }

            sf::Vector2f mousePos = static_cast<sf::Vector2f>(mm->position);

            for (auto& c : circuitBuilder.subComponents)
            {
                for (auto& p : c->currentOutputs)   // Only loop over outputs (no connecting in reverse for now)
                {
                    if(isMouseOver(mousePos, p->position, 10.0f))
                    {
                        p->highlighted = true;
                        inputState.highlightedPin = p; // Say it is "selected" as a flag for if it is clicked
                        return;
                    }
                    p->highlighted = false; // Set this so pins don't stay selected
                    inputState.highlightedPin = nullptr;
                }
            }    

            if (inputState.drawingWire)
            {
                inputState.drawingWire->tempEndPosition = mousePos;
            }
        }

        // Mouse click → place component
        if (auto* mp = event->getIf<sf::Event::MouseButtonPressed>())
        {
            if (mp->button == sf::Mouse::Button::Left && inputState.ghostComponent) // Moving ghost
            {
                circuitBuilder.addComponent(inputState.ghostComponent);
                inputState.ghostComponent = nullptr;    // THIS IS VITAL - otherwise program will think there is always a ghost
            }

            if(mp->button == sf::Mouse::Button::Left && !inputState.ghostComponent && inputState.highlightedPin)
            {
                inputState.selectedPin = inputState.highlightedPin;
                inputState.drawingWire = std::make_shared<Wire>();
                inputState.drawingWire->setStartPin(inputState.selectedPin);
            }

            if(mp->button == sf::Mouse::Button::Left && inputState.drawingWire && inputState.highlightedPin) // Finish drawing the wire
            {
                inputState.drawingWire->setEndPin(inputState.highlightedPin);
                inputState.drawingWire->linkPins();    // Links the pins so the logic should work
                renderState.wires.push_back(inputState.drawingWire);
                inputState.drawingWire = nullptr;
            }
        }
    }
}

bool Simulation::isMouseOver(const sf::Vector2f& mousePos, const sf::Vector2f& thingPos, float halfSize) {
    return mousePos.x >= thingPos.x - halfSize && mousePos.x <= thingPos.x + halfSize &&
           mousePos.y >= thingPos.y - halfSize && mousePos.y <= thingPos.y + halfSize;
}