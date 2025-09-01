#include "Simulation.h"


void Simulation::setupButtons()
{
    const int buttonWidth = 60;
    const int buttonHeight = 40;
    const int padding = 10;

    sf::Font globalFont;
    if (!globalFont.openFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    std::vector<std::string> buttonNames = { "And", "Or", "Not", "Input", "Output"};

    for (size_t i = 0; i < buttonNames.size(); ++i)
    {
        auto button = tgui::Button::create(buttonNames[i]);
        button->setSize(buttonWidth, buttonHeight);
        button->setPosition(padding + i * (buttonWidth + padding), window.getSize().y - padding - buttonHeight);

        if (buttonNames[i] == "And") // Would automate this but there are only five gates
        {
            button->onPress([this]() {
                auto component = std::make_shared<AndGate>();
                auto visualiser = ComponentVisualiser(component, gridSize); // construct visualiser from component
                placingVisualiser = std::make_shared<ComponentVisualiser>(visualiser);
            });
        }
        if (buttonNames[i] == "Or")
        {
            button->onPress([this]() {
                auto component = std::make_shared<OrGate>();
                auto visualiser = ComponentVisualiser(component, gridSize); 
                placingVisualiser = std::make_shared<ComponentVisualiser>(visualiser);
            });
        }

        if (buttonNames[i] == "Not")
        {
            button->onPress([this]() {
                auto component = std::make_shared<NotGate>();
                auto visualiser = ComponentVisualiser(component, gridSize); 
                placingVisualiser = std::make_shared<ComponentVisualiser>(visualiser);
            });
        }

        if (buttonNames[i] == "Input")
        {
            button->onPress([this]() {
                auto component = std::make_shared<InputGate>();
                auto visualiser = ComponentVisualiser(component, gridSize); 
                placingVisualiser = std::make_shared<ComponentVisualiser>(visualiser);
            });
        }

        if (buttonNames[i] == "Output")
        {
            button->onPress([this]() {
                auto component = std::make_shared<OutputGate>();
                auto visualiser = ComponentVisualiser(component, gridSize); 
                placingVisualiser = std::make_shared<ComponentVisualiser>(visualiser);
            });
        }

        gui.add(button);
    }
}

