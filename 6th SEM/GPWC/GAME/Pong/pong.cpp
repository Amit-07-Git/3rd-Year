////g++ pong.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include<SFML/Graphics.hpp>
using namespace sf;

int main() {
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Pong");
    View view(FloatRect(0, 0, 1920, 1080));
    
    bool paused = true;
    
    while (window.isOpen()) {
    //Handling the player input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
    }
    return 0;
}
