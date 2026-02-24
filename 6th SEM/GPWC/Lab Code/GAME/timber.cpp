#include<SFML/Graphics.hpp>
using namespace sf;
int main(){
  VideoMode vm(1920,1080);
  RenderWindow window(vm, "Timber");
  View view(FloatRect(0,0,1920,1080));
  
  Texture texturebackground;
  Texture texturetree;
  Texture texturebee;
  
  texturebackground.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/background.png"); 
  texturetree.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/tree.png");
  texturebee.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/bee.png");
  
  Sprite spriteBackground;
  Sprite spriteTree;
  Sprite spriteBee;
  
  spriteBackground.setTexture(texturebackground);
  spriteBackground.setPosition(0,0);
  
  spriteTree.setTexture(texturetree);
  spriteTree.setPosition(810, 0);
  
  spriteBee.setTexture(texturebee);
  spriteBee.setPosition(10, 800);
  
  while(window.isOpen()){
    //handle the players input
    Event event;
    while(window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape)){
      window.close();
    }
  //updates scene
  //draw scene
  window.clear();
  window.draw(spriteBackground);
  window.draw(spriteTree);
  window.draw(spriteBee);
  window.display();
  window.setView(view);
  }
  return 0;
}
