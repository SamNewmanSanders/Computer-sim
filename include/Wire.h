#pragma once

#include <memory>

#include "Components.h"

class Wire
{
public:
    std::shared_ptr<Pin> from; 
    std::shared_ptr<Pin> to;   

    Wire(std::shared_ptr<Pin> from, std::shared_ptr<Pin> to) : from(from), to(to) {}
};


