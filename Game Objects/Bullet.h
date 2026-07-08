//
// Created by chris on 7/6/26.
//

#include "../Engine Systems/Entity.h"

class Bullet : public Entity
{
    void update() override;
    void collided() override;
};
