#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Car{
protected:
    Sprite m_Shape;
    Vector2f m_Position;
    float m_Speed;

public:
    Car(float startX, float startY, float speed);
    virtual ~Car() = default;

    virtual void update(Time dt) = 0;

    void draw(RenderWindow &window);
    FloatRect getBounds() const;
    Vector2f getPosition() const;
};

class PlayerCar : public Car{
private:
    bool m_MovingLeft = false;
    bool m_MovingRight = false;

public:
    PlayerCar(float startX, float startY);

    void setTexture(const Texture &texture);
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();

    void update(Time dt) override;
};

class EnemyCar : public Car{
public:
    bool isActive;

    EnemyCar();

    void spawn(float startX, float startY, float speed, const Texture &texture);
    void update(Time dt) override;
};

class Game{
private:
    RenderWindow window;

    Texture playerTexture;
    Texture enemyTextures[5];

    PlayerCar player;

    static const int MAX_ENEMIES = 10;
    EnemyCar enemies[MAX_ENEMIES];

    Font font;
    Text scoreText;
    Text speedText;
    Text messageText;
    Text watermarkText;

    static const int NUM_DASHES = 6;
    RectangleShape roadDashes[NUM_DASHES];

    int score;
    float currentSpeedMultiplier;
    float spawnTimer;
    float spawnThreshold;

    bool gamestart;
    bool pause;
    bool isGameOver;
    bool acceptInput;

    void processEvents();
    void update(Time dt);
    void render();
    void spawnEnemy();
    void checkCollisions();
    void resetGame();
    void centerText(Text &text, float x, float y);

public:
    Game();
    void run();
};