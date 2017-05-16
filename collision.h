#pragma once
#include <cmath>

using namespace sf;

bool isCollide(Entity *a, Entity *b)
{
    if ((abs(b->posX - a->posX) <= ((a->width) / 4 + (b->width) / 4)) && (abs(b->posY - a->posY) <= ((a->height) / 4 + (b->height) / 4)))
        return true;
    else
        return false;
}