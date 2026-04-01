//g++ pong.cpp Ball.cpp Bat.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bat.h"
#include <sstream>
using namespace sf;

int main() {
    VideoMode vm(960, 580);
    RenderWindow window(vm, "Ping Pong");

    Clock clock;

    Ball ball(960/2, 100);
    Bat bat(960/2, 540-20);

    int score = 0;
    int lives = 3; 

    Font font;
    if(!font.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Pong/KOMIKAP_.ttf")) {
        return -1; 
    }

    Text hud;
    hud.setFont(font); 
    hud.setFillColor(Color::White);
    hud.setCharacterSize(30);
    hud.setPosition(20,20);

    while (window.isOpen()) {

        Time dt = clock.restart();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
            bat.moveLeft();
        else
            bat.stopLeft();

        if (Keyboard::isKeyPressed(Keyboard::Right))
            bat.moveRight();
        else
            bat.stopRight();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();


        ball.update(dt);
        bat.update(dt, window.getSize().x);
        if(ball.getPosition().left < 0 || 
            ball.getPosition().left + ball.getPosition().width > window.getSize().x){
            ball.reboundSides();
        }
        if(ball.getPosition().top<0){
            ball.reboundBatOrTop();
            score++;
        }
        
        std::stringstream ss; 
        ss << "Score: " << score << "  Lives: " << lives;
        hud.setString(ss.str());

        window.clear();
        window.draw(ball.getShape());
        window.draw(bat.getShape());
        window.draw(hud);
        window.display();
    }

    return 0;
}
