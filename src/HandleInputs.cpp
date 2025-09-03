#include "Simulation.h"

#include<iostream>

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
            }

            sf::Vector2f mousePos = static_cast<sf::Vector2f>(mm->position);

            inputState.highlightedInputPin = nullptr;   // Reset these before checking again
            inputState.highlightedOutputPin = nullptr; 
            inputState.selectedInputGate = nullptr;

            for (auto& c : circuitBuilder.subComponents)
            {
                // For changing input gate state
                sf::Vector2f topLeftPoint = c->position + sf::Vector2f(0, -renderState.padding*renderState.gridSize); // Quirk of how I'm drawing
                if (isMouseOverBox(mousePos, topLeftPoint , c->size))
                {
                    if (auto inputGate = std::dynamic_pointer_cast<InputGate>(c))
                    {
                        inputState.selectedInputGate = inputGate;
                    }
                }

                for (auto& p : c->currentOutputs)   // Only loop over outputs (no connecting in reverse for now)
                {
                    if(isMouseOverPoint(mousePos, p->position, 10.0f))
                    {
                        p->highlighted = true;
                        inputState.highlightedOutputPin = p; // Say it is "selected" as a flag for if it is clicked
                    }
                    else p->highlighted = false; // Set this so pins don't stay selected
                }

                for (auto& p : c->inputs)   
                {
                    if(isMouseOverPoint(mousePos, p->position, 10.0f))
                    {
                        p->highlighted = true;
                        inputState.highlightedInputPin = p; 
                    }
                    else p->highlighted = false; 
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

            // Select the first input pin to start drawing wire
            else if(mp->button == sf::Mouse::Button::Left && !inputState.ghostComponent && inputState.highlightedOutputPin && !inputState.drawingWire)
            {
                inputState.drawingWire = std::make_shared<Wire>();
                inputState.drawingWire->setStartPin(inputState.highlightedOutputPin);

                // initialize temp positions so the wire doesn't jump to 0,0
                inputState.drawingWire->tempStartPosition = inputState.highlightedOutputPin->position;
                inputState.drawingWire->tempEndPosition   = inputState.highlightedOutputPin->position;
            }

             //Finish drawing the wire
            else if(mp->button == sf::Mouse::Button::Left && inputState.drawingWire && inputState.highlightedInputPin)
            {                   
                inputState.drawingWire->setEndPin(inputState.highlightedInputPin);
                inputState.drawingWire->linkPins();    // Links the pins so the logic should work
                renderState.wires.push_back(inputState.drawingWire);
                inputState.drawingWire = nullptr;
            }
            // Toggle an outputGates state
            else if(mp->button == sf::Mouse::Button::Left && inputState.selectedInputGate)
            {
                inputState.selectedInputGate->toggleInput();
            }
        }
    }
}

bool Simulation::isMouseOverPoint(const sf::Vector2f& mousePos, const sf::Vector2f& thingPos, float halfSize) {
    return mousePos.x >= thingPos.x - halfSize && mousePos.x <= thingPos.x + halfSize &&
           mousePos.y >= thingPos.y - halfSize && mousePos.y <= thingPos.y + halfSize;
}

bool Simulation::isMouseOverBox(const sf::Vector2f& mousePos,
                                const sf::Vector2f& pos,
                                const sf::Vector2f& size)
{
    return mousePos.x >= pos.x &&
           mousePos.x <= pos.x + size.x &&
           mousePos.y >= pos.y &&
           mousePos.y <= pos.y + size.y;
}
