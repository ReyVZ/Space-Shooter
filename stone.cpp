#include <SFML/Graphics.hpp>
#include <cmath>
#include "stone.h"

using namespace sf;

Stone::Stone(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY) : Entity(Tag, T, X, Y, Width, Height, PosX, PosY)
{
    frame = 0;
    dist = 0;
    life = 100;
}

void Stone::update(RenderWindow &window, Entity *e)
{
    frame++;
    if (frame >= 30)
    {
        x += 64;
        if (x >= 1024)
            x = 0;
        frame = 0;
    }
    sprite.setTextureRect(IntRect(x, y, width, height));

    if (e->life)
    {
        dist = sqrt((e->posX - posX) * (e->posX - posX) + (e->posY - posY) * (e->posY - posY));
        posX += 0.1 * (e->posX - posX) / dist;
        posY += 0.1 * (e->posY - posY) / dist;
    }

    sprite.setPosition(posX, posY);
    if (life != 0)
        window.draw(sprite);
}
