#include<SFML/Graphics.hpp>
#include<sstream>
using namespace sf;

int main() {
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber");
    View view(FloatRect(0, 0, 1920, 1080));

    Texture texturebackground;
    Texture texturetree;
    Texture texturebee;
    Texture texturecloud;

    texturebackground.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/background.png");
    texturetree.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/tree.png");
    texturebee.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/bee.png");
    texturecloud.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/graphics/cloud.png");

    Sprite spriteBackground;
    spriteBackground.setTexture(texturebackground);
    spriteBackground.setPosition(0, 0);

    Sprite spriteTree;
    spriteTree.setTexture(texturetree);
    spriteTree.setPosition(810, 0);

    Sprite spriteBee;
    spriteBee.setTexture(texturebee);
    spriteBee.setPosition(1, 800);
    bool beeActive = false;
    float beeSpeed = 0.0f;

    Sprite spriteCloud1;
    spriteCloud1.setTexture(texturecloud);
    spriteCloud1.setPosition(0, 0);
    bool cloud1Active = false;
    float cloud1Speed = 0.0f;

    Sprite spriteCloud2;
    spriteCloud2.setTexture(texturecloud);
    spriteCloud2.setPosition(0, 250);
    bool cloud2Active = false;
    float cloud2Speed = 0.0f;

    Sprite spriteCloud3;
    spriteCloud3.setTexture(texturecloud);
    spriteCloud3.setPosition(0, 500);
    bool cloud3Active = false;
    float cloud3Speed = 0.0f;

    Clock clock;
    bool paused = true;
    
    Font font;
    font.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_prereq/fonts/KOMIKAP_.ttf");
    Text messageText;
    Text scoreText;
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to Start");
    scoreText.setString("Score = 0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::Red);
    
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left+textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    
    messageText.setPosition(1920/2.0f, 1080/2.0f);
    scoreText.setPosition(20,20);

    while (window.isOpen()) {
    //handle the players input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
        }
        
      //updates scene
        Time dt = clock.restart();
        if(!paused){
        
        if (!beeActive) {
            srand((int)time(0) * 10);
            beeSpeed = (rand() % 200) + 200;
            srand((int)time(0) * 20);
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = true;
        } else {
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }
        
        if (!cloud1Active) {
            cloud1Speed = (rand() % 200)+25;
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;
        } else {
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
            if (spriteCloud1.getPosition().x > 1920) {
                cloud1Active = false;
            }
        }
        if (!cloud2Active) {
            cloud2Speed = (rand() % 200)+50;
            srand((int)time(0) * 10);
            float height = (rand() % 150) + 50;
            spriteCloud2.setPosition(-100, height);
            cloud2Active = true;
        } else {
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
            if (spriteCloud2.getPosition().x > 1920) {
                cloud2Active = false;
            }
        }
        if (!cloud3Active) {
            cloud3Speed = (rand() % 200)+100;
            srand((int)time(0) * 10);
            float height = (rand() % 100) + 100;
            spriteCloud3.setPosition(-100, height);
            cloud3Active = true;
        } else {
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
            if (spriteCloud3.getPosition().x > 1920) {
                cloud3Active = false;
            }
        }
        }

        // Draw scene
        window.clear();
        window.draw(spriteBackground);
        
        window.draw(spriteTree);
        
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        
        window.draw(spriteBee);
        
        window.draw(messageText);
        window.draw(scoreText);
        
        window.display();
        window.setView(view);
    }
    return 0;
}
