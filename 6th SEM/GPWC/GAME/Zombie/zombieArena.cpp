// g++ zombieArena.cpp -o zombie -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include <SFML/Graphics.hpp>
#include "player.cpp"

using namespace sf;

int main() {
    enum class state {PAUSED, LEVELING_UP, GAME_OVER, PLAYING };
    
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie");

    Vertex lineX[2];
    lineX[0].position = Vector2f(0, resolution.y / 2);
    lineX[0].color = Color::Green;
    lineX[1].position = Vector2f(resolution.x, resolution.y / 2);
    lineX[1].color = Color::Green;

    Vertex lineY[2];
    lineY[0].position = Vector2f(resolution.x / 2, 0);
    lineY[0].color = Color::Green;
    lineY[1].position = Vector2f(resolution.x / 2, resolution.y);
    lineY[1].color = Color::Green;

    RectangleShape windowRect(Vector2f(resolution.x, resolution.y));
    windowRect.setOutlineThickness(5);
    windowRect.setFillColor(Color::Red);

    RectangleShape rectArena;
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    Clock clock;
    Time gameTimeTotal;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    bool paused = false;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == Keyboard::Return) {
                    paused = !paused;
                }
            }
        }

        window.clear();
        window.draw(windowRect);
        window.draw(lineX, 2, Lines);
        window.draw(lineY, 2, Lines);
        window.display();
    }
    return 0;
}
