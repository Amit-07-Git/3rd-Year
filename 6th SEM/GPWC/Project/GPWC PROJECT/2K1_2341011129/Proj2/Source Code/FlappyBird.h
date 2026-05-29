#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Bird.h"
#include "Pipe.h"

using namespace sf;

class FlappyBird{
private:
    RenderWindow window;

    Texture birdTexture;
    Texture pipeTexture;

    Bird player;

    static const int MAX_PIPES = 5;
    Pipe pipes[MAX_PIPES];

    Font font;
    Text scoreText;
    Text highScoreText;
    Text messageText;
    Text watermarkText;

    int score;
    int highScore;
    float gameSpeed;
    bool isGameOver;
    bool isGameStarted;

    void loadHighScore();
    void saveHighScore();
    void processEvents();
    void update(Time dt);
    void render();
    void resetGame();

public:
    FlappyBird();
    void run();
};