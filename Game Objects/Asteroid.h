//
// Created by chris on 7/6/26.
//

#pragma once
#include "../Engine Systems/Entity.h"

class Asteroid : public Entity
{
    void update() override;
    void collided() override;
};
