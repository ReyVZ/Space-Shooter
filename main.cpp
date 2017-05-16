#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <sstream>
#include "entity.h"
#include "player.h"
#include "stone.h"
#include "collision.h"
#include "explosion.h"
#include "erasor.h"
#include "laser.h"

using namespace sf;

const float SPEED = 0.4;
const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Space Shooter");
    Mouse::setPosition(Vector2i(100, 100), window);

    // ======================GRAPHICS=========================

    Texture spaceT, playerT, stoneT, explosionAT, explosionBT, laserT;
    spaceT.loadFromFile("images/background.jpg");
    playerT.loadFromFile("images/spaceship.png");
    stoneT.loadFromFile("images/rock.png");
    explosionAT.loadFromFile("images/type_A.png");
    explosionBT.loadFromFile("images/type_B.png");
    laserT.loadFromFile("images/fire_red.png");

    Sprite background;
    background.setTexture(spaceT);

    RectangleShape noHP(Vector2f(100, 10));
    RectangleShape HP(Vector2f(100, 10));
    noHP.setFillColor(Color::Black);
    noHP.setPosition(105, 32);
    noHP.setOutlineThickness(2);
    noHP.setOutlineColor(Color::White);
    HP.setFillColor(Color::Red);
    HP.setPosition(105, 32);

    // ======================TEXTS=========================

    Font font;
    font.loadFromFile("fonts/RaviPrakash-Regular.ttf");
    Text scoreText, healthText, GOText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(550, 20);
    scoreText.setStyle(Text::Bold | Text::Underlined);
    healthText.setFont(font);
    healthText.setCharacterSize(24);
    healthText.setPosition(20, 20);
    healthText.setString("Health: ");
    healthText.setStyle(Text::Bold | Text::Underlined);
    GOText.setFont(font);
    GOText.setCharacterSize(72);
    GOText.setPosition(240, 220);
    GOText.setString("GAME OVER");
    GOText.setStyle(Text::Bold);

    // ======================SOUNDS=========================

    Music music;
    music.openFromFile("sounds/click.wav");
    music.play();
    music.setLoop(true);
    music.setVolume(50);

    SoundBuffer laserBuffer, explosionBuffer, kaboomBuffer;
    laserBuffer.loadFromFile("sounds/laser.wav");
    explosionBuffer.loadFromFile("sounds/explosion.wav");
    kaboomBuffer.loadFromFile("sounds/kaboom.wav");
    Sound laserSound, explosionSound, kaboomSound;
    laserSound.setBuffer(laserBuffer);
    explosionSound.setBuffer(explosionBuffer);
    kaboomSound.setBuffer(kaboomBuffer);

    // ======================INIT LISTS TIMERS & PLAYER=======================

    std::list<Entity *> enemies;
    std::list<Entity *> explosions;
    std::list<Entity *> bullets;

    Player *p = new Player("player", playerT, 39, 40, 39, 45, 400, 300);

    Clock shootTimer;
    Clock waveTimer;

    // ======================MAIN LOOP=========================

    while (window.isOpen())
    {
        float shootTime = shootTimer.getElapsedTime().asMilliseconds();
        if (p->life && shootTime >= 200)
        {
            p->readyShoot = true;
            shootTimer.restart();
        }
        float waveTime = waveTimer.getElapsedTime().asSeconds();
        if (p->life && waveTime >= 3)
        {
            Stone *s1 = new Stone("stone", stoneT, 0, 0, 64, 64, 400, 0);
            enemies.push_back(s1);
            Stone *s2 = new Stone("stone", stoneT, 0, 0, 64, 64, 800, 300);
            enemies.push_back(s2);
            Stone *s3 = new Stone("stone", stoneT, 0, 0, 64, 64, 400, 600);
            enemies.push_back(s3);
            Stone *s4 = new Stone("stone", stoneT, 0, 0, 64, 64, 0, 300);
            enemies.push_back(s4);
            waveTimer.restart();
        }

        // ======================EVENTS=========================

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            p->dX = -SPEED;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            p->dX = SPEED;
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            p->dY = -SPEED;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            p->dY = SPEED;
        }
        if (Mouse::isButtonPressed(Mouse::Left) && p->life > 0)
        {
            if (p->readyShoot)
            {
                Laser *l = new Laser("laser", laserT, 0, 0, 32, 64, p->posX, p->posY, window);
                laserSound.play();
                bullets.push_back(l);
                p->readyShoot = false;
            }
        }

        // ======================COLLISIONS=========================

        for (auto e : enemies)
        {
            if (e->tag == "stone" && isCollide(p, e))
            {
                e->life = 0;
                if (p->life > 0)
                    p->life -= 20;
                else
                    p->life = 0;
                if (p->life == 0)
                {
                    Explosion *explB = new Explosion("explosionB", explosionBT, 0, 0, 192, 192, p->posX, p->posY);
                    music.stop();
                    kaboomSound.play();
                    explosions.push_back(explB);
                }
            }
            for (auto b : bullets)
            {
                if (b->tag == "laser" && isCollide(b, e))
                {
                    b->life = 0;
                    e->life -= 10;
                }
            }
            if (e->life == 0)
            {
                Explosion *explA = new Explosion("explosionA", explosionAT, 0, 0, 50, 50, e->posX, e->posY);
                explosionSound.play();
                explosions.push_back(explA);
                p->score++;
            }
        }
        erasor(enemies);
        erasor(explosions);
        erasor(bullets);

        // ======================UPDATES & DISPLAY=========================

        std::ostringstream ost;
        ost << p->score;
        std::string count = ost.str();
        scoreText.setString("Asteroids killed: " + count);

        window.clear();
        window.draw(background);

        for (auto e : enemies)
            e->update(window, p);
        for (auto e : explosions)
            e->update(window, p);
        for (auto e : bullets)
            e->update(window, p);
        p->update(window);
        if (p->life == 0)
            window.draw(GOText);
        HP.setSize(Vector2f(p->life, 10));
        window.draw(healthText);
        window.draw(scoreText);
        window.draw(noHP);
        window.draw(HP);
        window.display();
    }

    return 0;
}