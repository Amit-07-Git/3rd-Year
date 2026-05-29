#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bird{
private:
    Sprite m_Shape;
    Vector2f m_Position;
    float m_VelocityY;
    float m_Gravity;
    float m_FlapStrength;

public:
    Bird();
    void setTexture(const Texture &texture);
    void update(Time dt);
    void flap();
    FloatRect getBounds() const;
    Vector2f getPosition() const;
    void reset();
};