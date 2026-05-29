#include "Game.h"
#include <sstream>
#include <cstdlib>

Car::Car(float startX, float startY, float speed) : m_Speed(speed){
    m_Position.x = startX;
    m_Position.y = startY;
}

void Car::draw(RenderWindow &window) { 
    window.draw(m_Shape); 
}
FloatRect Car::getBounds() const { 
    return m_Shape.getGlobalBounds(); 
}
Vector2f Car::getPosition() const { 
    return m_Position; 
}

PlayerCar::PlayerCar(float startX, float startY) : Car(startX, startY, 400.0f){
    m_Shape.setPosition(m_Position);
}

void PlayerCar::setTexture(const Texture &texture) { 
    m_Shape.setTexture(texture); 
}
void PlayerCar::moveLeft() { 
    m_MovingLeft = true; 
}
void PlayerCar::moveRight() { 
    m_MovingRight = true; 
}
void PlayerCar::stopLeft() { 
    m_MovingLeft = false; 
}
void PlayerCar::stopRight() { 
    m_MovingRight = false; 
}
void PlayerCar::update(Time dt){
    if (m_MovingLeft)
        m_Position.x -= m_Speed * dt.asSeconds();
    if (m_MovingRight)
        m_Position.x += m_Speed * dt.asSeconds();
    float carWidth = m_Shape.getGlobalBounds().width;

    if (m_Position.x < 0)
        m_Position.x = 0;
    if (m_Position.x > 800.f - carWidth)
        m_Position.x = 800.f - carWidth;

    m_Shape.setPosition(m_Position);
}

EnemyCar::EnemyCar() : Car(0.f, 0.f, 0.f), isActive(false) {}

void EnemyCar::spawn(float startX, float startY, float speed, const Texture &texture){
    m_Shape.setTexture(texture, true);

    float carWidth = m_Shape.getGlobalBounds().width;

    if (startX > 800.f - carWidth){
        startX = 800.f - carWidth;
    }

    m_Position.x = startX;
    m_Position.y = startY;
    m_Speed = speed;
    isActive = true;
    m_Shape.setPosition(m_Position);
}

void EnemyCar::update(Time dt){
    if (!isActive)
        return;
    m_Position.y += m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
}

void Game::centerText(Text &text, float x, float y){
    FloatRect details = text.getLocalBounds();
    text.setOrigin(details.left + details.width / 2.0f, details.top + details.height / 2.0f);
    text.setPosition(x, y);
}

Game::Game() : window(VideoMode(800, 600), "2D Car Dodging Game"),
               player(375.f, 430.f), score(0),
               currentSpeedMultiplier(1.0f), spawnTimer(0.f),
               spawnThreshold(1.5f), isGameOver(false),
               gamestart(false), pause(true), acceptInput(true)
{
    window.setFramerateLimit(60);
    for (int i = 0; i < NUM_DASHES; i++){
        roadDashes[i].setSize(Vector2f(10.f, 70.f));
        roadDashes[i].setFillColor(Color::White);
        roadDashes[i].setPosition(395.f, i * 130.f);
    }

    font.loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Font/KOMIKAP_.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(28);
    scoreText.setFillColor(Color::Yellow);

    speedText.setFont(font);
    speedText.setCharacterSize(28);
    speedText.setFillColor(Color::Yellow);

    messageText.setFont(font);
    messageText.setCharacterSize(40);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start !!!!");
    centerText(messageText, 400.f, 300.f);

    watermarkText.setFont(font);
    watermarkText.setString("Reg No: 2341011129");
    watermarkText.setCharacterSize(20);
    watermarkText.setFillColor(Color(255, 0, 0, 100));
    watermarkText.setPosition(600.f, 560.f);

    playerTexture.loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/WhiteCar.png");
    player.setTexture(playerTexture);

    enemyTextures[0].loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/RedCar1.png");
    enemyTextures[1].loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/RedCar2.png");
    enemyTextures[2].loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/YellowCar1.png");
    enemyTextures[3].loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/YellowCar2.png");
    enemyTextures[4].loadFromFile("/mnt/g/wsl/GPWC/CarDodgingGame/Graphics/YellowCar3.png");
}

void Game::run(){
    Clock clock;
    while (window.isOpen()){
        processEvents();
        Time dt = clock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents(){
    Event event;
    while (window.pollEvent(event)){
        if (event.type == Event::Closed)
            window.close();
        if (event.type == Event::KeyReleased && !acceptInput){
            acceptInput = true;
        }
    }

    if (acceptInput){
        if (Keyboard::isKeyPressed(Keyboard::Enter)){
            if (isGameOver){
                resetGame();
            }
            else{
                gamestart = true;
                pause = false;
                messageText.setString("");
            }
            acceptInput = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space) && gamestart && !isGameOver){
            pause = !pause;
            messageText.setString(pause ? "Game is Paused !!!" : "");
            centerText(messageText, 400.f, 300.f);
            acceptInput = false;
        }
    }

    if (!pause && gamestart && !isGameOver){
        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
            player.moveLeft();
        else
            player.stopLeft();

        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
            player.moveRight();
        else
            player.stopRight();
    }
    else{
        player.stopLeft();
        player.stopRight();
    }
}

void Game::update(Time dt){
    if (pause || !gamestart || isGameOver)
        return;
    player.update(dt);
    float roadSpeed = 300.f * currentSpeedMultiplier;
    for (int i = 0; i < NUM_DASHES; i++){
        roadDashes[i].move(0.f, roadSpeed * dt.asSeconds());
        if (roadDashes[i].getPosition().y > 600.f)
            roadDashes[i].setPosition(395.f, -100.f);
    }

    spawnTimer += dt.asSeconds();
    if (spawnTimer >= spawnThreshold){
        spawnEnemy();
        spawnTimer = 0.f;
        score += 10;

        if (spawnThreshold > 0.4f)
            spawnThreshold -= 0.05f;
        currentSpeedMultiplier += 0.05f;
    }

    for (int i = 0; i < MAX_ENEMIES; i++){
        if (enemies[i].isActive){
            enemies[i].update(dt);

            if (enemies[i].getPosition().y > 600.f){
                enemies[i].isActive = false;
            }
        }
    }
    checkCollisions();

    scoreText.setString("SCORE: " + std::to_string(score));
    centerText(scoreText, 200.f, 30.f);

    speedText.setString("SPEED: " + std::to_string((int)(currentSpeedMultiplier * 10)));
    centerText(speedText, 600.f, 30.f);
}

void Game::spawnEnemy(){
    int lane = rand() % 4;
    float startX = 100.f + (lane * 150.f);
    float randomSpeed = (200.f + (rand() % 100)) * currentSpeedMultiplier;
    int randomCarImage = rand() % 5;

    for (int i = 0; i < MAX_ENEMIES; i++){
        if (!enemies[i].isActive){
            enemies[i].spawn(startX, -100.f, randomSpeed, enemyTextures[randomCarImage]);
            break;
        }
    }
}

void Game::checkCollisions(){
    FloatRect playerBounds = player.getBounds();
    for (int i = 0; i < MAX_ENEMIES; i++){
        if (enemies[i].isActive && playerBounds.intersects(enemies[i].getBounds())){
            isGameOver = true;
            pause = true;
            gamestart = false;

            messageText.setString("GAME OVER !!!!!\nPress Enter to restart");
            centerText(messageText, 400.f, 300.f);
        }
    }
}

void Game::render(){
    window.clear(Color(50, 50, 50));
    for (int i = 0; i < NUM_DASHES; i++)
        window.draw(roadDashes[i]);

    player.draw(window);
    for (int i = 0; i < MAX_ENEMIES; i++){
        if (enemies[i].isActive)
            enemies[i].draw(window);
    }

    window.draw(scoreText);
    window.draw(speedText);

    if (!gamestart || pause || isGameOver)
        window.draw(messageText);

    window.draw(watermarkText);
    window.display();
}

void Game::resetGame(){
    score = 0;
    currentSpeedMultiplier = 1.0f;
    spawnThreshold = 1.5f;

    for (int i = 0; i < MAX_ENEMIES; i++)
        enemies[i].isActive = false;

    isGameOver = false;
    gamestart = true;
    pause = false;
    messageText.setString("");

    player = PlayerCar(375.f, 430.f);
    player.setTexture(playerTexture);
}