//g++ zombieArena.cpp -o zombie -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include<SFML/Graphics.hpp>
#include "player.cpp"
using namespace sf;
int main(){
  Vector2f resolution;
  resolution.x = VideoMode::getDesktopMode().width;
  resolution.y = VideoMode::getDesktopMode().height;
  RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie");
  
  RectangleShape windowRect(Vector2f(resolution.x, resolution.y));
  windowRect.setFillColor(Color::Green);
  
  while(window.isOpen()){
    Event event;
    bool paused = false;
    while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }       
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
    }
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
    }
    
            
            
    window.clear();          //window.clear(Color::Green);
    window.draw(windowRect);
    window.display();
  }
  return 0;
}

