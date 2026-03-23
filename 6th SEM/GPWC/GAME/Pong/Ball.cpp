#include "Ball.h"
Ball::Ball(float startX, float startY){
  m_Position.x = startX;
  m_Position.y = startY;
  m_Shape.setRadius(10);
  m_Shape.sePosition(m_Position);
}
FloatRect Ball::getPosition(){
  return m_Shape.getGlobalBounds();
}
CircleShape Ball::getShape(){
  return m_Shape;
}
void Ball::reboundSides(){
  m_DirectionX = -m_DirectionX;
}
void Ball::reboundBatOrTop(){
  m_DirectionY = -m_DirectionY;
}
