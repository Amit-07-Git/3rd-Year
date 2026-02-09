#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

const int WIDTH = 1920;
const int HEIGHT = 1080;

int main() {
    srand(time(nullptr));

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Timberman");
    window.setFramerateLimit(60);

    // Player
    RectangleShape player(Vector2f(50, 100));
    player.setFillColor(Color::Red);
    player.setPosition(300, 450);

    bool playerLeft = true;

    // Tree trunk
    RectangleShape trunk(Vector2f(80, 400));
    trunk.setFillColor(Color(139, 69, 19));
    trunk.setPosition(360, 150);

    // Branch
    RectangleShape branch(Vector2f(150, 30));
    branch.setFillColor(Color::Green);
    bool branchLeft = rand() % 2;

    auto updateBranch = [&]() {
        branchLeft = rand() % 2;
        branch.setPosition(branchLeft ? 200 : 450, 200);
    };

    updateBranch();

    int score = 0;
    Font font;
    font.loadFromFile("arial.ttf");

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left) {
                    playerLeft = true;
                    player.setPosition(300, 450);
                }
                if (event.key.code == Keyboard::Right) {
                    playerLeft = false;
                    player.setPosition(450, 450);
                }

                // Chop
                score++;
                updateBranch();

                // Game over check
                if (playerLeft == branchLeft) {
                    score = 0; // reset
                }
            }
        }

        scoreText.setString("Score: " + to_string(score));

        window.clear(Color::Black);
        window.draw(trunk);
        window.draw(branch);
        window.draw(player);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}

