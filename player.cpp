#include <SFML/Graphics.hpp>
#include <cmath>
#include "player.h"

using namespace sf;

Player::Player(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY) : Entity(Tag, T, X, Y, Width, Height, PosX, PosY)
{
    frame = 0;
    life = 100;
    score = 0;
    readyShoot = false;
}

void Player::update(RenderWindow &window, Entity *e)
{
    posX += dX;
    posY += dY;
    if (posX <= 0 || posX >= WIDTH)
        posX -= dX;
    if (posY <= 0 || posY >= HEIGHT)
        posY -= dY;
    sprite.setPosition(posX, posY);

    frame++;
    if (frame >= 50)
    {
        if (y == 86)
            y = 40;
        else if (y == 0)
            y = 40;
        else
            y += 46;
        frame = 0;
        height = 45;
    }
    if (dX == 0 && dY == 0)
    {
        y = 0;
        height = 39;
    }
    sprite.setTextureRect(IntRect(x, y, width, height));

    Vector2i mPos = Mouse::getPosition(window);
    float turnX = mPos.x - posX;
    float turnY = mPos.y - posY;
    float rotation = (atan2(turnY, turnX)) * 180 / 3.14159265;
    sprite.setRotation(rotation + 90);

    dX = dY = 0;
    if (life != 0)
        window.draw(sprite);
}
