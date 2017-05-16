#pragma once
#include "entity.h"

using namespace sf;

extern const int WIDTH;
extern const int HEIGHT;

class Laser : public Entity
{
private:
  int frame;
  float dist, dirX, dirY;

public:
  Laser(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY, RenderWindow &window);

  void update(RenderWindow &window, Entity *e = 0);
};