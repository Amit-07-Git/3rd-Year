#pragma once
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
using namespace sf;
class Player{
  private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    Vector2f m_Position;
    Texture m_Texture;
    Sprite m_sprite;
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
    Time getLastHItTime();
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
    void update(float elapsedTime, Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void IncreaseHealthLevel(int amount);
    void resetPlayerStats();
};

Player::Player(){
  m_Speed = START_SPEED;
  m_Health = START_HEALTH;
  m_MaxHealth = START_HEALTH;
  m_Texture.loadFromFile("/home/iteradmin/Music/23412K1 6th Sem/ZombieAssets/graphics/player.png");
  m_Sprite.setTexture(m_Texture);
  m_Sprite.setOrigin(25,25);
  m_Sprite.SetPosition(1920/2.0f, 1080/2.0f);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize){
  m_Position.x = arena.width/2;
  m_Position.y = arena.height/2;
  m_Arena.left = arena.left;
  m_Arena.top = arena.top;
  m_Arena.width = arena.width;
  m_Arena.height = arena.height;
  m_TileSize = tileSize;
  m_Resolution.x = resolution.x;
  m_Resolution.y = resolution.y;
  m_Sprite.setPosition(m_Position);
}

bool Player::hit(Time timehit){
  if(timehit.asMilliseconds() - m_LastHit.asMilliseconds() > 200){
    m_LastHit = timehit;
    m_Health -= 10
    return true;
  }
  else{
    return false;
  }
}

FloatRect Player::getPosition(){
  return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter(){
  return m_position;
}

float Player::getRotation(){
  return m_Sprite.getPosition();
}

Sprite Player::getSprite(){
  return m_Sprite;
}

int Player::getHealth(){
  return m_Health;
}

void Player::moveLeft(){
  m_leftPressed = true;
}
void Player::moveRight(){
  m_RightPressed = true;
}
void Player::moveUp(){
  m_UpPressed = true;
}
void Player::moveDown(){
  m_DownPressed = true;
}
void Player::stopLeft(){
  m_leftPressed = false;
}
void Player::stopRight(){
  m_RightPressed = false;
}
void Player::stopUp(){
  m_UpPressed = false;
}
void Player::stopDown(){
  m_DownPressed = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition){
  if(m_UpPressed){
    m_Position.y -= m_Speed * elapsedTime;
  }
  if(m_DownPressed){
    m_Position.y += m_Speed * elapsedTime;
  }
  if(m_LeftPressed){
    m_Position.x -= m_Speed * elapsedTime;
  }
  if(m_RightPressed){
    m_Position.x += m_Speed * elapsedTime;
  }
  m_Sprite.setPosition(m_Position);
  
  if(m_Position.x > m_Arena.width - m_TileSize){
    m_Position.x = m_Arena.width - m_TileSize;
  }
  if(m_Position.x < m_Arena.left + m_TileSize){
    m_Position.x = m_Arena.left + m_TileSize;
  }
  if(m_Position.y > m_Arena.height - m_TileSize){
    m_Position.y = m_Arena.height - m_TileSize;
  }
  if(m_Position.y < m_Arena.top + m_TileSize){
    m_Position.y = m_Arena.top + m_TileSize;
  }
  Vector2i playerScreenPosition = window.mapCoordsToPixel(m_Position);
  float angle = (atan2(mousePosition.y - playerScreenPosition.y, mousePosition.x - playerScreenPosition.x)*180)/3.141;
  m_sprite.setRotation(angle);
}
void Player::upgradeSpeed(){
  m_Speed += (START_SPEED*.2);
}
void Player::upgradeHealth(){
  m_Health += (START_HEALTH*.2);
}
void Player::increaseHealthLevel(int amount){
  m_Health += amount;
  if(m_Health > m_MaxHealth){
    m_Health = m_MaxHealth;
  }
}


int main(){

  return 0;
}
