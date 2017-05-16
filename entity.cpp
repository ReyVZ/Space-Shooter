#include <SFML/Graphics.hpp>
#include "entity.h"

using namespace sf;

Entity::Entity(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY) : tag(Tag), texture(T), x(X), y(Y), width(Width), height(Height), posX(PosX), posY(PosY)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(x, y, width, height));
    sprite.setOrigin(width / 2, height / 2);
    dX = dY = 0;
}

void Entity::update(RenderWindow &window, Entity *e) {}