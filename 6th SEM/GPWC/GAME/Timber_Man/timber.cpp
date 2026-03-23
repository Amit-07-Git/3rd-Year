////g++ timber.cpp -o tim -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
using namespace sf;

void updateBranches(int seed);
const int NUMBER_BRANCHES = 6;
Sprite branches[NUMBER_BRANCHES];
enum class side{LEFT,RIGHT,NONE};
side branchPositions[NUMBER_BRANCHES];

int main() {
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber");
    View view(FloatRect(0, 0, 1920, 1080));

    Texture texturebackground;
    Texture texturetree;
    Texture texturebee;
    Texture texturecloud;
    Texture textureplayer;
    Texture texturerip;
    Texture textureaxe;
    Texture texturelog;

    texturebackground.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/background.png");
    texturetree.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/tree.png");
    texturebee.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Mangraphics/bee.png");
    texturecloud.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/cloud.png");
    textureplayer.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/player.png");
    texturerip.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/rip.png");
    textureaxe.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/axe.png");
    texturelog.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/log.png");

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
    
    Sprite spritePlayer;
    spritePlayer.setTexture(textureplayer);
    spritePlayer.setPosition(580,720);
    side playside = side::LEFT;
    
    Sprite spriteRIP;
    spriteRIP.setTexture(texturerip);
    spriteRIP.setPosition(600,860);
    
    Sprite spriteLog;
    spriteLog.setTexture(texturelog);
    spriteLog.setPosition(810,720);
    
    Sprite spriteAxe;
    spriteAxe.setTexture(textureaxe);
    spriteAxe.setPosition(700,830);
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    Clock clock;
    bool paused = true;
    
    Font font;
    font.loadFromFile("/home/iteradmin/Music/6th Semester/GDWC/GAME/Timber_Man/fonts/KOMIKAP_.ttf");
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
    
    int score = 0; 
    
    RectangleShape timebar;
    float timebarstartwidth = 400;
    float timebarheight = 80;
    timebar.setSize(Vector2f(timebarstartwidth,timebarheight));
    timebar.setFillColor(Color::Green);
    timebar.setPosition(1920/2 - timebarstartwidth/2, 980);
    
    Time gametimetotal;
    float timeremaining = 6.0f;
    float timebarstartwidthpersecond = timebarstartwidth/timeremaining;
    
    Texture textureBranch;
    textureBranch.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/graphics/branch.png");
    for(int i = 0; i <NUMBER_BRANCHES; i++){
      branches[i].setTexture(textureBranch);
      branches[i].setPosition(-2000, -2000);
      branches[i].setOrigin(220,40);
    }

    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    bool acceptInput = false;
    
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
    
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
    
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("/home/iteradmin/Music/6th Semester/GPWC/GAME/Timber_Man/sound/out_of_time.wav");
    Sound oot;
    oot.setBuffer(ootBuffer);
    
    while (window.isOpen()) {
    //Handling the player input
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            timeremaining = 6.0f;
            paused = false;
            score = 0;
            for(int i = 0; i< NUMBER_BRANCHES;i++){
              branchPositions[i] = side::NONE;
            }
            spriteRIP.setPosition(675,2000);
            spritePlayer.setPosition(580,720);
            spriteAxe.setPosition(700,830);
            acceptInput = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)){
          paused = true;
          messageText.setString("Paused!");
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left+textRect.width/2.0f,textRect.top+textRect.height/2.0f);
          messageText.setPosition(1920/2.0f,1080/2.0f);
        }
        if(acceptInput){
          if(Keyboard::isKeyPressed(Keyboard::Right)){
            playside = side::RIGHT;
            score++;
            timeremaining+=(2.0f/score)+.15f;
            spritePlayer.setPosition(1200,720);
            spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
            updateBranches(score);
            spriteLog.setPosition(810,720);
            logSpeedX = -2500;
            logActive = true;
            acceptInput = false;
            chop.play();
          }
          if(Keyboard::isKeyPressed(Keyboard::Left)){
            playside = side::LEFT;
            score++;
            timeremaining+=(2.0f/score)+.15f;
            spritePlayer.setPosition(580,720);
            spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
            updateBranches(score);
            spriteLog.setPosition(810,720);
            logSpeedX = 2500;
            logActive = true;
            acceptInput = false;
            chop.play();
          }
        }
        
        if(!paused){
          Time dt = clock.restart();
          timeremaining -= dt.asSeconds();
          timebar.setSize(Vector2f(timebarstartwidthpersecond*timeremaining, timebarheight));
        if (timeremaining<=0.0f){
          paused=true;
          messageText.setString("Out of Time!");
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left+textRect.width/2.0f,textRect.top+textRect.height/2.0f);
          messageText.setPosition(1920/2.0f,1080/2.0f);
          oot.play();
        }
        
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
        
        std::stringstream ss;
        ss<<"Score="<<score;
        scoreText.setString(ss.str());
        
        for(int i = 0; i <NUMBER_BRANCHES; i++){
          float height = i*150;
          if(branchPositions[i] == side::LEFT){
            branches[i].setPosition(610,height);
            branches[i].setRotation(180);
          } else if(branchPositions[i] == side::RIGHT){
            branches[i].setPosition(1330,height);
            branches[i].setRotation(0);
          } else {
            branches[i].setPosition(3000,height);
          }
        }
        
        
        if(logActive){
          spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
          spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));       
          if(spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000){
            logActive = false;
            spriteLog.setPosition(810,720);
          }
        }
        if(branchPositions[5] == playside){
          //death
          paused = true;
          acceptInput = false;
          spriteRIP.setPosition(525,760);
          spritePlayer.setPosition(2000,660);
          spriteAxe.setPosition(2000,660);
          messageText.setString("SQUASHED!");
          FloatRect textRect = messageText.getLocalBounds();
          messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
          messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
          death.play();
        }
        
        }

        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timebar);
        window.draw(spritePlayer);
        window.draw(spriteLog);
        window.draw(spriteAxe);
        window.draw(spriteRIP);
        for(int i = 0; i <NUMBER_BRANCHES; i++){
          window.draw(branches[i]);
        }
        if(paused) {
            window.draw(messageText);
        }
        window.display();
        window.setView(view);
    }
    return 0;
}

void updateBranches(int seed){
  for(int j = NUMBER_BRANCHES-1; j>0; j--){
    branchPositions[j] = branchPositions[j-1];
  }
  srand((int)time(0)+seed);
  int r = (rand()%5);
  switch(r){
    case 0:
      branchPositions[0] = side::LEFT;
      break;
    case 1:
      branchPositions[0] = side::RIGHT;
      break;
    default:
      branchPositions[0] = side::NONE;
      break;
  }
}
