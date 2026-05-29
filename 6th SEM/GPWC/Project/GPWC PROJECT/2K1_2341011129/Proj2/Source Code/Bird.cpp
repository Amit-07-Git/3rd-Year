#include "Bird.h"

Bird::Bird()
{
    m_Gravity = 1500.0f;
    m_FlapStrength = 500.0f;
    reset();
}

void Bird::setTexture(const Texture &texture)
{
    m_Shape.setTexture(texture);
    m_Shape.setScale(0.03f, 0.03f);
}

void Bird::update(Time dt)
{
    m_VelocityY += m_Gravity * dt.asSeconds();
    m_Position.y += m_VelocityY * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}

void Bird::flap()
{
    m_VelocityY = -m_FlapStrength;
}

FloatRect Bird::getBounds() const
{
    return m_Shape.getGlobalBounds();
}

Vector2f Bird::getPosition() const
{
    return m_Position;
}

void Bird::reset()
{
    m_Position.x = 200.f;
    m_Position.y = 300.f;
    m_VelocityY = 0.f;
    m_Shape.setPosition(m_Position);
}