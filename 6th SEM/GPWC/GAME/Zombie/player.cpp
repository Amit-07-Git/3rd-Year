#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

class Player {
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    Vector2f m_Position;
    Texture m_Texture;
    Sprite m_Sprite;
    Vector2f m_Resolution;
    int m_TileSize;
    bool m_UpPressed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;
    int m_Health;
    int m_MaxHealth;
    Time m_LastHit;
    float m_Speed;
    IntRect m_Arena;

public:
    Player();
    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    bool hit(Time timeHit);
    Time getLastHitTime();
    FloatRect getPosition();
    Vector2f getCenter();
    Sprite getSprite();
    int getHealth();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void stopLeft();
    void stopRight();
    void stopUp();
    void stopDown();
    void update(float elapsedTime, Vector2i mousePosition, RenderWindow& window);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    void resetPlayerStats();
};

Player::Player() {
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
    m_Texture.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Zombie/ZombieAssets/graphics/player.png");
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin(25, 25);
    m_UpPressed = false;
    m_DownPressed = false;
    m_LeftPressed = false;
    m_RightPressed = false;
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize) {
    m_Position.x = arena.width / 2.0f;
    m_Position.y = arena.height / 2.0f;
    m_Arena = arena;
    m_TileSize = tileSize;
    m_Resolution = resolution;
    m_Sprite.setPosition(m_Position);
}

Time Player::getLastHitTime() {
    return m_LastHit;
}

bool Player::hit(Time timehit) {
    if (timehit.asMilliseconds() - m_LastHit.asMilliseconds() > 200) {
        m_LastHit = timehit;
        m_Health -= 1;
        return true;
    }
    return false;
}

FloatRect Player::getPosition() {
    return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter() {
    return m_Position;
}

Sprite Player::getSprite() {
    return m_Sprite;
}

int Player::getHealth() {
    return m_Health;
}

void Player::moveLeft() { m_LeftPressed = true; }
void Player::moveRight() { m_RightPressed = true; }
void Player::moveUp() { m_UpPressed = true; }
void Player::moveDown() { m_DownPressed = true; }
void Player::stopLeft() { m_LeftPressed = false; }
void Player::stopRight() { m_RightPressed = false; }
void Player::stopUp() { m_UpPressed = false; }
void Player::stopDown() { m_DownPressed = false; }

void Player::update(float elapsedTime, Vector2i mousePosition, RenderWindow& window) {
    if (m_UpPressed) m_Position.y -= m_Speed * elapsedTime;
    if (m_DownPressed) m_Position.y += m_Speed * elapsedTime;
    if (m_LeftPressed) m_Position.x -= m_Speed * elapsedTime;
    if (m_RightPressed) m_Position.x += m_Speed * elapsedTime;

    m_Sprite.setPosition(m_Position);

    if (m_Position.x > m_Arena.width - m_TileSize) m_Position.x = m_Arena.width - m_TileSize;
    if (m_Position.x < m_Arena.left + m_TileSize) m_Position.x = m_Arena.left + m_TileSize;
    if (m_Position.y > m_Arena.height - m_TileSize) m_Position.y = m_Arena.height - m_TileSize;
    if (m_Position.y < m_Arena.top + m_TileSize) m_Position.y = m_Arena.top + m_TileSize;

    Vector2f playerScreenPosition = (Vector2f)window.mapCoordsToPixel(m_Position, window.getView());
    float angle = (atan2(mousePosition.y - playerScreenPosition.y, mousePosition.x - playerScreenPosition.x) * 180) / 3.141;
    m_Sprite.setRotation(angle);
}

void Player::upgradeSpeed() { 
  m_Speed += (START_SPEED * .2); 
}
void Player::upgradeHealth() { 
  m_MaxHealth += (START_HEALTH * .2); 
}
void Player::increaseHealthLevel(int amount) {
    m_Health += amount;
    if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
}

void Player::resetPlayerStats() {
    m_Speed = START_SPEED;
    m_Health = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}
