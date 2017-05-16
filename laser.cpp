#include <SFML/Graphics.hpp>
#include "laser.h"

using namespace sf;

Laser::Laser(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY, RenderWindow &window) : Entity(Tag, T, X, Y, Width, Height, PosX, PosY)
{
    frame = 0;
    life = 1;

    Vector2i mPos = Mouse::getPosition(window);
    float turnX = mPos.x - posX;
    float turnY = mPos.y - posY;
    float rotation = (atan2(turnY, turnX)) * 180 / 3.14159265;
    sprite.setRotation(rotation + 90);

    dist = sqrt((mPos.x - posX) * (mPos.x - posX) + (mPos.y - posY) * (mPos.y - posY));
    dirX = (mPos.x - posX) / dist;
    dirY = (mPos.y - posY) / dist;
}

void Laser::update(RenderWindow &window, Entity *e)
{
    frame++;
    if (frame >= 100)
    {
        x += width;
        if (x >= 512)
            x = 0;
        frame = 0;
    }
    sprite.setTextureRect(IntRect(x, y, width, height));

    posX += dirX;
    posY += dirY;

    if (posX <= 0 || posX >= WIDTH || posY <= 0 || posY >= HEIGHT)
        life = 0;
    sprite.setPosition(posX, posY);
    if (life != 0)
        window.draw(sprite);
}
