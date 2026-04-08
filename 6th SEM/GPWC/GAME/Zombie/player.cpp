
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
  m_Texture.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Zombie/ZombieAssets/graphics/player.png");
  m_Sprite.setTexture(m_Texture);
  m_Sprite.setOrigin(25,25);
  m_Sprite.SetPosition(1920/2.0f, 1080/2.0f);
}


int main(){

  return 0;
}
