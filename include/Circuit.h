#pragma once

#include <vector>
#include <memory>

#include "Components.h"

// Make Circuit inherit component so layers of abstraction can be created
class Circuit : public Component
{
public:
    Circuit(std::vector<std::shared_ptr<Component>> subComponents,
            std::vector<std::shared_ptr<Pin>> inputPins, 
            std::vector<std::shared_ptr<Pin>> outputPins);
    
    void computeNextOutputs() override;

    std::vector<std::shared_ptr<Component>> subComponents;  // Make public so renderer can access

};
