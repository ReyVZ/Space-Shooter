#pragma once
#include "entity.h"

using namespace sf;

class Explosion : public Entity
{
  private:
    int frame;

  public:
    Explosion(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY);

    void update(RenderWindow &window, Entity *e);
};