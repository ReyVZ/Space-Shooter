#pragma once
#include "entity.h"
#include "player.h"

using namespace sf;

class Stone : public Entity
{
  private:
    int frame;
    float dist;

  public:
    Stone(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY);

    void update(RenderWindow &window, Entity *e);
};