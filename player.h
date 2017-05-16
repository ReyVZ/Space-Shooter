#pragma once
#include "entity.h"

using namespace sf;

extern const int WIDTH;
extern const int HEIGHT;

class Player : public Entity
{
private:
  int frame;

public:
  Player(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY);
  int score;
  bool readyShoot;
  void update(RenderWindow &window, Entity *e = 0);
};