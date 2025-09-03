#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>

class Pin {
public:

    bool value = false;
    std::shared_ptr<Pin> connectedFrom = nullptr; // The what inputs to this pin (can only be a single output)
    std::vector<std::shared_ptr<Pin>> connectedTo; // The pins this output connects to (can be multiple)

    sf::Vector2f position; // Location on screen (makes rendering easier if each pin knows its location)
    bool highlighted = false;  // If the pin is currently below mouse (turn yellow)
};


class Component
{
public:
    std::vector<std::shared_ptr<Pin>> inputs; 
    std::vector<std::shared_ptr<Pin>> currentOutputs;
    std::vector<bool> nextOutputs;

    sf::Vector2f position;  // Keep links to rendering minimal, just neccesary info
    sf::Vector2f size;       

    virtual void computeNextOutputs() = 0;
    void updateOutputs() 
    {
        for (size_t i = 0; i < currentOutputs.size(); ++i) 
        {
            currentOutputs[i]->value = nextOutputs[i];
            for (auto& targetPin : currentOutputs[i]->connectedTo) 
            {
                targetPin->value = nextOutputs[i];  // propagate downstream
            }
        }   
    }
};

class AndGate : public Component
{
public:
    
    AndGate()
    {
        inputs = { std::make_shared<Pin>(), std::make_shared<Pin>() };
        currentOutputs = { std::make_shared<Pin>() };
        nextOutputs.resize(1);
    }


    void setInput(int index, std::shared_ptr<Pin> pin)
    {
        inputs[index] = pin;  // Note the index starts at 0!
    }

    void computeNextOutputs() override
    {
        if (inputs[0]->connectedFrom && inputs[1]->connectedFrom) {
            nextOutputs[0] = inputs[0]->value && inputs[1]->value;
        }
        else {
            nextOutputs[0] = false; // If either input is nullptr, output false
        }
    } 
};

class OrGate : public Component
{
public:
    
    OrGate()
    {
        inputs = { std::make_shared<Pin>(), std::make_shared<Pin>() };
        currentOutputs = { std::make_shared<Pin>() };
        nextOutputs.resize(1);
    }

    void setInput(int index, std::shared_ptr<Pin> pin)
    {
        inputs[index] = pin;  
    }

    void computeNextOutputs() override
    {
        if (inputs[0]->connectedFrom && inputs[1]->connectedFrom) {
            nextOutputs[0] = inputs[0]->value || inputs[1]->value;
        }
        else {
            nextOutputs[0] = false; 
        }
    }
};

class NotGate : public Component
{
public:
    
    NotGate()
    {
        inputs = { std::make_shared<Pin>() };
        currentOutputs = { std::make_shared<Pin>() };
        nextOutputs.resize(1);
    }


    void setInput(std::shared_ptr<Pin> pin)
    {
        inputs[0] = pin;
    }

    void computeNextOutputs() override
    {
        if (inputs[0]->connectedFrom) {
            nextOutputs[0] = !inputs[0]->value;
        }
        else {
            nextOutputs[0] = false;
        }
    } 
};

class InputGate : public Component
{
public:

    InputGate()
    {
        inputs.resize(0);
        currentOutputs = { std::make_shared<Pin>() };
        nextOutputs.resize(1);
    }

    void toggleInput()
    {
        currentOutputs[0]->value = !currentOutputs[0]->value;
        nextOutputs[0] = !nextOutputs[0];

    }

    void computeNextOutputs() override
    {
        // No logic for input gate
    }
};

class OutputGate : public Component
{
public:

    bool value; // Make it easy to read

    OutputGate()
    {
        inputs = { std::make_shared<Pin>() };
        currentOutputs.resize(0);
        nextOutputs.resize(0);
    }

    void setInput(std::shared_ptr<Pin> pin)
    {
        inputs[0] = pin;
    }

    void computeNextOutputs() override
    {
        if (inputs[0]->connectedFrom) {
            value = inputs[0]->value;
        }
        else {
            value = false;
        }
    }
};