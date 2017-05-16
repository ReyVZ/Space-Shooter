#pragma once

using namespace sf;

void erasor(std::list<Entity *> &entities)
{
    for (auto i = entities.begin(); i != entities.end(); i++)
    {
        Entity *e = *i;
        if (e->life == 0)
        {
            i = entities.erase(i);
            delete e;
        }
    }
}