#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Pin {
public:
    bool value = false;
    std::shared_ptr<Pin> connectedFrom = nullptr; // The what inputs to this pin (can only be a single output)
    std::vector<std::shared_ptr<Pin>> connectedTo; // The pins this output connects to (can be multiple)
};


class Component
{
public:
    std::vector<std::shared_ptr<Pin>> inputs; 
    std::vector<std::shared_ptr<Pin>> currentOutputs;
    std::vector<bool> nextOutputs;

    virtual void computeNextOutputs() = 0;
    void updateOutputs() 
    {
        for (size_t i = 0; i < currentOutputs.size(); ++i) {
            currentOutputs[i]->value = nextOutputs[i];
        }
    }

    std::string type = "GENERIC";
};

class AndGate : public Component
{
public:
    
    AndGate()
    {
        inputs.resize(2); // Two input pins
        currentOutputs.resize(1); // One output pin
        nextOutputs.resize(1);
    }


    void setInput(int index, std::shared_ptr<Pin> pin)
    {
        inputs[index] = pin;  // Note the index starts at 0!
    }

    void computeNextOutputs() override
    {
        if (inputs[0] && inputs[1]) {
            nextOutputs[0] = inputs[0]->value && inputs[1]->value;
        }
        else {
            nextOutputs[0] = false; // If either input is nullptr, output false
        }
    } 

    std::string type = "AND";
};

class OrGate : public Component
{
public:
    
    OrGate()
    {
        inputs.resize(2); 
        currentOutputs.resize(1);
        nextOutputs.resize(1);
    }

    void setInput(int index, std::shared_ptr<Pin> pin)
    {
        inputs[index] = pin;  
    }

    void computeNextOutputs() override
    {
        if (inputs[0] && inputs[1]) {
            nextOutputs[0] = inputs[0]->value || inputs[1]->value;
        }
        else {
            nextOutputs[0] = false; 
        }
    }

    std::string type = "OR";
};

class NotGate : public Component
{
public:
    
    NotGate()
    {
        inputs.resize(1); 
        currentOutputs.resize(1);
        nextOutputs.resize(1);
    }


    void setInput(std::shared_ptr<Pin> pin)
    {
        inputs[0] = pin;
    }

    void computeNextOutputs() override
    {
        if (inputs[0]) {
            nextOutputs[0] = !inputs[0]->value;
        }
        else {
            nextOutputs[0] = false;
        }
    } 

    std::string type = "NOT";
};

class InputGate : public Component
{
public:

    InputGate()
    {
        inputs.resize(0);
        currentOutputs.resize(1);
        nextOutputs.resize(1);
    }

    void setInput(bool value)
    {
        nextOutputs[0] = value;
    }

    void computeNextOutputs() override
    {
        // No logic for input gate
    }

    std::string type = "INPUT";
};

class OutputGate : public Component
{
public:

    bool value; // Make it easy to read

    OutputGate()
    {
        inputs.resize(1);
        currentOutputs.resize(0);
        nextOutputs.resize(0);
    }

    void setInput(std::shared_ptr<Pin> pin)
    {
        inputs[0] = pin;
    }

    void computeNextOutputs() override
    {
        if (inputs[0]) {
            value = inputs[0]->value;
        }
        else {
            value = false;
        }
    }

    std::string type = "OUTPUT";
};