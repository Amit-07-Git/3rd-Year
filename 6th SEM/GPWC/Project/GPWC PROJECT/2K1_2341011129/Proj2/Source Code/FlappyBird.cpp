#include "FlappyBird.h"
#include <sstream>
#include <cstdlib>

FlappyBird::FlappyBird() : window(VideoMode(800, 600), "Flappy!!!"),
                           score(0), highScore(0), gameSpeed(250.0f),
                           isGameOver(false), isGameStarted(false)
{
    window.setFramerateLimit(60);

    loadHighScore();

    font.loadFromFile("/mnt/g/wsl/GPWC/Flappy/Font/KOMIKAP_.ttf");

    birdTexture.loadFromFile("/mnt/g/wsl/GPWC/Flappy/Graphics/Bird.png");
    player.setTexture(birdTexture);

    pipeTexture.loadFromFile("/mnt/g/wsl/GPWC/Flappy/Graphics/Pipes.png");

    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color::Black);
    scoreText.setPosition(50, 20);

    highScoreText.setFont(font);
    highScoreText.setCharacterSize(35);
    highScoreText.setFillColor(Color::White);
    highScoreText.setOutlineColor(Color::Black);
    highScoreText.setOutlineThickness(2.0f);
    highScoreText.setPosition(450, 20);

    messageText.setFont(font);
    messageText.setCharacterSize(40);
    messageText.setFillColor(Color::Black);
    messageText.setPosition(150, 250);
    messageText.setString("Press SPACE to Start");

    watermarkText.setFont(font);
    watermarkText.setString("Reg No: 2341011129");
    watermarkText.setCharacterSize(20);
    watermarkText.setFillColor(Color(255, 0, 0, 100));
    watermarkText.setPosition(600.f, 560.f);

    resetGame();
}

void FlappyBird::loadHighScore(){
    std::ifstream file("assets/highscore.txt");
    if (file.is_open()){
        file >> highScore;
        file.close();
    }
    else{
        highScore = 0;
    }
}

void FlappyBird::saveHighScore(){
    std::ofstream file("assets/highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

void FlappyBird::run(){
    Clock clock;
    while (window.isOpen()){
        processEvents();

        Time dt = clock.restart();
        if (isGameStarted && !isGameOver){
            update(dt);
        }

        render();
    }
}

void FlappyBird::processEvents(){
    Event event;
    while (window.pollEvent(event)){
        if (event.type == Event::Closed)
            window.close();

        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space){
            if (!isGameStarted){
                isGameStarted = true;
                player.flap();
            }
            else if (isGameOver){
                resetGame();
                isGameStarted = true;
                player.flap();
            }
            else
                player.flap();
        }
    }
}

void FlappyBird::update(Time dt){
    player.update(dt);

    FloatRect birdBounds = player.getBounds();

    if (birdBounds.top < 0 || birdBounds.top + birdBounds.height > 600)
        isGameOver = true;

    for (int i = 0; i < MAX_PIPES; i++){
        pipes[i].update(dt);

        if (pipes[i].checkCollision(birdBounds))
            isGameOver = true;

        if (!pipes[i].isPassed() && pipes[i].getX() + 50.f < player.getPosition().x){
            pipes[i].setPassed();
            score++;
        }

        if (pipes[i].getX() < -100.f){
            float highestX = 0;
            for (int j = 0; j < MAX_PIPES; j++){
                if (pipes[j].getX() > highestX)
                    highestX = pipes[j].getX();
            }
            float newGapY = 150.f + (rand() % 300);
            pipes[i].spawn(highestX + 300.f, newGapY, 150.f, gameSpeed, pipeTexture);
        }
    }

    if (isGameOver){
        if (score > highScore){
            highScore = score;
            saveHighScore();
        }
        messageText.setString("GAME OVER!\nPress SPACE to Restart");
    }

    scoreText.setString("SCORE: " + std::to_string(score));
    highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
}

void FlappyBird::resetGame(){
    score = 0;
    isGameOver = false;
    isGameStarted = false;
    player.reset();

    messageText.setString("Press SPACE to Start");

    float startX = 600.f;
    for (int i = 0; i < MAX_PIPES; i++){
        float randomGapY = 150.f + (rand() % 300);
        pipes[i].spawn(startX + (i * 300.f), randomGapY, 150.f, gameSpeed, pipeTexture);
    }

    scoreText.setString("SCORE: 0");
    highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
}

void FlappyBird::render(){
    window.clear(Color::White);

    for (int i = 0; i < MAX_PIPES; i++){
        pipes[i].draw(window);
    }

    Sprite birdSprite;
    birdSprite.setTexture(birdTexture);
    birdSprite.setPosition(player.getPosition());
    window.draw(birdSprite);

    window.draw(scoreText);
    window.draw(highScoreText);

    if (!isGameStarted || isGameOver)
        window.draw(messageText);

    window.draw(watermarkText);
    window.display();
}