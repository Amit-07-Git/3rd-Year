#include "Ball.h"

Ball::Ball(float startX, float startY){
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(10);
    m_Shape.setFillColor(Color::White);
    m_Shape.setPosition(m_Position); 
}

FloatRect Ball::getPosition(){ 
    return m_Shape.getGlobalBounds();
}

const CircleShape& Ball::getShape(){ 
    return m_Shape;
}

void Ball::reboundSides(){
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop(){
    m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom(){
    m_Position.x = 250;
    m_Position.y = 11;
}

void Ball::update(Time dt){ 
    m_Position.x += m_DirectionX * m_speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_speed * dt.asSeconds(); 
    m_Shape.setPosition(m_Position);
}
