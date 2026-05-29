#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pipe{
private:
    Sprite m_TopPipe;
    Sprite m_BottomPipe;
    float m_X;
    float m_Speed;
    bool m_IsPassed;
    bool m_IsActive;

public:
    Pipe();
    void spawn(float startX, float gapY, float gapHeight, float speed, const Texture &texture);
    void update(Time dt);
    bool checkCollision(FloatRect birdBounds) const;
    void draw(RenderWindow &window);
    float getX() const;
    bool isPassed() const;
    void setPassed();
};