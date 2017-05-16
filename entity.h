#pragma once

using namespace sf;

class Entity
{
public:
  Entity(std::string Tag, Texture &T, float X, float Y, float Width, float Height, float PosX, float PosY);

  Texture texture;
  Sprite sprite;
  std::string tag;
  float x, y, width, height, posX, posY, dX, dY;
  int life;

  virtual void update(RenderWindow &window, Entity *e);
};