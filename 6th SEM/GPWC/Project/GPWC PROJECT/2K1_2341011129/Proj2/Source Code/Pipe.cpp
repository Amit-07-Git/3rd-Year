#include "Pipe.h"

Pipe::Pipe() : m_IsPassed(false), m_IsActive(false) {}

void Pipe::spawn(float startX, float gapY, float gapHeight, float speed, const Texture &texture)
{
    m_X = startX;
    m_Speed = speed;
    m_IsPassed = false;
    m_IsActive = true;

    m_TopPipe.setTexture(texture);
    m_BottomPipe.setTexture(texture);

    // FIX: Anchor the pipes to the gap and stretch them to the edges of the window

    // Top Pipe: Cap is at the gap. The -2.5f scale flips it UPWARD and stretches it to the ceiling.
    m_TopPipe.setOrigin(0.f, 0.f);
    m_TopPipe.setPosition(m_X, gapY - (gapHeight / 2.0f));
    m_TopPipe.setScale(1.f, -2.5f);

    // Bottom Pipe: Cap is at the gap. The 2.5f scale stretches it DOWNWARD to the floor.
    m_BottomPipe.setOrigin(0.f, 0.f);
    m_BottomPipe.setPosition(m_X, gapY + (gapHeight / 2.0f));
    m_BottomPipe.setScale(1.f, 2.5f);
}

void Pipe::update(Time dt)
{
    if (!m_IsActive)
        return;

    m_X -= m_Speed * dt.asSeconds();
    m_TopPipe.setPosition(m_X, m_TopPipe.getPosition().y);
    m_BottomPipe.setPosition(m_X, m_BottomPipe.getPosition().y);
}

bool Pipe::checkCollision(FloatRect birdBounds) const
{
    if (!m_IsActive)
        return false;

    // SFML handles negative scales perfectly for collision bounds
    if (m_TopPipe.getGlobalBounds().intersects(birdBounds) ||
        m_BottomPipe.getGlobalBounds().intersects(birdBounds))
    {
        return true;
    }
    return false;
}

void Pipe::draw(RenderWindow &window)
{
    if (!m_IsActive)
        return;
    window.draw(m_TopPipe);
    window.draw(m_BottomPipe);
}

float Pipe::getX() const { return m_X; }
bool Pipe::isPassed() const { return m_IsPassed; }
void Pipe::setPassed() { m_IsPassed = true; }