#include "Bat.h"
Bat::Bat(float startX, float startY) : m_Position(startX, startY) {
    m_Shape.setSize(Vector2f(100.f, 10.f));
    m_Shape.setFillColor(Color::White);
    m_Shape.setPosition(m_Position);
}

FloatRect Bat::getPosition() const {
    return m_Shape.getGlobalBounds();
}

const RectangleShape& Bat::getShape() const {
    return m_Shape;
}

void Bat::moveLeft() { 
  m_MovingLeft = true; 
}
void Bat::moveRight() { 
  m_MovingRight = true; 
}
void Bat::stopLeft() { 
  m_MovingLeft = false; 
}
void Bat::stopRight() { 
  m_MovingRight = false; 
}

void Bat::update(Time dt, float screenWidth) {
    if (m_MovingLeft && m_Position.x > 0)
        m_Position.x -= m_Speed * dt.asSeconds();

    if (m_MovingRight && m_Position.x < 860)
        m_Position.x += m_Speed * dt.asSeconds();

    m_Shape.setPosition(m_Position);
}
