#include "Simulation.h"

void Simulation::setupButtons()
{
    const int buttonWidth = 80;
    const int buttonHeight = 40;
    const int padding = 10;

    sf::Font globalFont;
    if (!globalFont.openFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    std::vector<std::string> buttonNames = { "And", "Or", "Not", "Input", "Output", "Finish Circuit"};

    for (size_t i = 0; i < buttonNames.size(); ++i)
    {
        auto button = tgui::Button::create(buttonNames[i]);
        button->setSize(buttonWidth, buttonHeight);
        button->setPosition(padding + i * (buttonWidth + padding), window.getSize().y - padding - buttonHeight);

        if (buttonNames[i] == "And") // Would automate this but there are only five gates
        {
            button->onPress([this]() {
                inputState.ghostComponent = std::make_shared<AndGate>();
                inputState.ghostComponent->position = sf::Vector2f(100.f, 100.f);
            });
        }

        if (buttonNames[i] == "Input") 
        {
            button->onPress([this]() {
                inputState.ghostComponent = std::make_shared<InputGate>();
            });
        }


        if (buttonNames[i] == "Output") 
        {
            button->onPress([this]() {
                inputState.ghostComponent = std::make_shared<OutputGate>();
            });
        }


        if (buttonNames[i] == "Finish Circuit") // Would automate this but there are only five gates
        {
            button->onPress([this]() {
                // TODO - ADD FINISH CIRCUIT LOGIC
            });
        }

        gui.add(button);
    }
}