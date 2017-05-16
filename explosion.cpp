#include <SFML/Graphics.hpp>
#include "explosion.h"

using namespace sf;

Explosion::Explosion(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY) : Entity(Tag, T, X, Y, Width, Height, PosX, PosY)
{
    frame = 0;
    life = 1;
}

void Explosion::update(RenderWindow &window, Entity *e)
{
    frame++;
    if (frame >= 30)
    {
        x += width;
        if (x >= 12288)
            life = 0;
        frame = 0;
    }
    sprite.setTextureRect(IntRect(x, y, width, height));

    sprite.setPosition(posX, posY);
    if (life != 0)
        window.draw(sprite);
}
