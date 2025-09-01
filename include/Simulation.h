#pragma once

#include <SFML/Graphics.hpp>  // SFML 3
#include <SFML/Window.hpp> 
#include <SFML/System.hpp> 

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <vector>

#include "Components.h"
#include "ComponentVisualiser.h"
#include "Renderer.h"


class Simulation
{
public:
    Simulation();

    void run();

private:

    void update();

    // Rendering
    void render();
    float gridSize = 40.f;

    // Helpers
    void drawGrid();
    void setupButtons();
    void findPinAt(sf::Vector2f mousePos);
    

    sf::RenderWindow window;
    tgui::Gui gui;
    Renderer renderer;


    std::vector<std::shared_ptr<Component>> components;    // Must use pointers because of polymorphism
    std::vector<std::shared_ptr<ComponentVisualiser>> componentVisualisers;

    // Event handling 
    void handleEvents();
    bool updateSim = false;

    std::shared_ptr<ComponentVisualiser> placingVisualiser = nullptr; // Nullptr initially as no component is being placed
};