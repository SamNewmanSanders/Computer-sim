#pragma once

#include <vector>
#include <memory>

#include "Components.h"
#include "Circuit.h"

class CircuitBuilder    // This class is to build circuits (doesn't inherit component yet)
{
public:

    std::vector<std::shared_ptr<Component>> subComponents;
    std::vector<std::shared_ptr<Pin>> inputs;   
    std::vector<std::shared_ptr<Pin>> outputs;

    void addComponent(std::shared_ptr<Component> comp);
    void connect(std::shared_ptr<Pin> from, std::shared_ptr<Pin> to);

    std::shared_ptr<Circuit> finalizeComponent();
};