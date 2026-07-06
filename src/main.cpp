/* Rida Fatima, Maneha Bint E Tariq
2503567, 2503565
PF Project*/

#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
Text menuText;
enum GameState
{
    STATE_MENU,
    STATE_LEVEL_SELECT,   
    STATE_GAME,
    STATE_PAUSE,
    STATE_HELP,
    STATE_HIGHSCORES     
};


GameState currentState = STATE_MENU;
// 🔹 GRID OFFSET (already using)
const int OFFSET_X = 70;
const int OFFSET_Y = 31;

// 🔹 HIGH SCORE PANEL START X (RIGHT SIDE)
const int HS_X = OFFSET_X + 180 + 20;
bool gameOver = false;
int highScores[10] = {0};
int currentLevel = 1;
int main(){
    srand(time(0));
    loadHighScores();

    RenderWindow window(VideoMode(320, 480), title);
    window.setFramerateLimit(60);

    Texture obj1, obj2, obj3;
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */

    //Sprite sprite(obj1), background(obj2), frame(obj3);
    Sprite sprite;
    Sprite background;
    Sprite frame;

    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");

    sprite.setTexture(obj1);
    background.setTexture(obj2);
    frame.setTexture(obj3);

    // === BACKGROUND POSITION & SCALE (ADD HERE) ===
    background.setPosition(0, 0);

    background.setScale(
        window.getSize().x / (float)obj2.getSize().x,
        window.getSize().y / (float)obj2.getSize().y
    );


    // Frame fixed position (original offsets ke mutabiq)
    frame.setPosition(42, 10);

    Font font;
    font.loadFromFile("img/arial.ttf"); // koi bhi .ttf font
    menuText.setFont(font);
    menuText.setCharacterSize(20);
    menuText.setFillColor(Color::White);


    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(15, 8);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(28);
    gameOverText.setFillColor(Color::Red);
    // Center alignment (horizontal)
    FloatRect goBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(goBounds.width / 2, goBounds.height / 2);
    gameOverText.setPosition(320 / 2, 480 / 2 - 30);

    Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(24);
    finalScoreText.setFillColor(Color::White);

    Text restartText;
    restartText.setFont(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(18);
    restartText.setFillColor(Color::White);

    FloatRect rBounds = restartText.getLocalBounds();
    restartText.setOrigin(rBounds.width / 2, rBounds.height / 2);
    restartText.setPosition(320 / 2, 480 / 2 + 60);

    Text hsTitle;
    hsTitle.setFont(font);
    hsTitle.setString("HIGH SCORES");
    hsTitle.setCharacterSize(18);
    hsTitle.setFillColor(Color::White);
    hsTitle.setPosition(HS_X, 80);

    Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(16);
    highScoreText.setFillColor(Color::White);

    int delta_x=0;
    float timer=0, delay=0.3;
    bool rotate=0;
    Clock clock;
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {
                if (currentState == STATE_MENU) {
                if (e.key.code == Keyboard::Num1)
                    currentState = STATE_LEVEL_SELECT;
                else if (e.key.code == Keyboard::Num2)
                    currentState = STATE_HIGHSCORES;
                else if (e.key.code == Keyboard::Num3)
                    currentState = STATE_HELP;
                else if (e.key.code == Keyboard::Num4)
                    window.close();
                continue;
                }                                           //If any other key (not cross) is pressed
                if (currentState == STATE_HELP && e.key.code == Keyboard::Escape) {
                    currentState = STATE_MENU;
                continue;
                }
                if (currentState == STATE_LEVEL_SELECT)
                {
                    if (e.key.code == Keyboard::Num1) {
                        currentLevel = 1;   // Beginner
                        delay = 0.4f;
                        restartGame();
                        currentState = STATE_GAME;
                }
                    else if (e.key.code == Keyboard::Num2) {
                        currentLevel = 2;   // Advanced
                        delay = 0.12f;
                        restartGame();
                        currentState = STATE_GAME;
                }
                    else if (e.key.code == Keyboard::Escape) {
                        currentState = STATE_MENU;
                }
                    continue;
                }
            if (currentState == STATE_HIGHSCORES && e.key.code == Keyboard::Escape)
                    currentState = STATE_MENU;
                                          
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::P && currentState == STATE_GAME)
                    currentState = STATE_PAUSE;
                if (currentState == STATE_PAUSE) {
                if (e.key.code == Keyboard::Num1) {
                    currentState = STATE_LEVEL_SELECT;
                }
                else if (e.key.code == Keyboard::Num3)
                    currentState = STATE_HELP;
                else if (e.key.code == Keyboard::Num4)
                    window.close();
                else if (e.key.code == Keyboard::Num5)
                    currentState = STATE_GAME;
                }
                else if (e.key.code == Keyboard::R && gameOver)
                    restartGame();
                }
        }
    if (currentState == STATE_GAME && Keyboard::isKeyPressed(Keyboard::Down))         //Just another way to detect key presses without event listener
        delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
    if (currentState == STATE_MENU) {
        window.clear();
        window.draw(background);
        menuText.setString(
            "TETRIS GAME\n\n"
            "1. Start New Game\n"
            "2. High Scores\n"   
            "3. Help\n"
            "4. Exit"
        );
    FloatRect m = menuText.getLocalBounds();
        menuText.setOrigin(m.width / 2, m.height / 2);
        menuText.setPosition(320 / 2, 240);

           window.draw(menuText);
           window.display();
    continue;
    }
    if (currentState == STATE_LEVEL_SELECT)
    {
        window.clear();
        window.draw(background);
        menuText.setString(
            "SELECT LEVEL\n\n"
            "1. Beginner\n"
            "2. Advanced\n\n"
            "ESC : Back"
        );

    FloatRect l = menuText.getLocalBounds();
    menuText.setOrigin(l.width / 2, l.height / 2);
    menuText.setPosition(320 / 2, 240);

    window.draw(menuText);
    window.display();
    continue;
    }
    if (currentState == STATE_HIGHSCORES)
    {
        window.clear();
        window.draw(background);

        menuText.setString("HIGH SCORES\n");
        menuText.setPosition(320 / 2, 60);
        window.draw(menuText);

    for (int i = 0; i < 10; i++)
    {
        highScoreText.setString(
            std::to_string(i + 1) + ". " + std::to_string(highScores[i])
        );
        highScoreText.setPosition(100, 120 + i * 25);
        window.draw(highScoreText);
    }

    Text back;
    back.setFont(font);
    back.setString("ESC : Back");
    back.setCharacterSize(16);
    back.setPosition(100, 400);
    window.draw(back);

    window.display();
    continue;
    }

    if (currentState == STATE_HELP) {
           window.clear();
           window.draw(background);
        menuText.setString(
        "HELP\n\n"
        "Arrow Keys : Move\n"
        "Up Arrow   : Rotate\n"
        "Down Arrow : Drop\n"
        "P          : Pause\n"
        "R          : Restart\n\n"
        "ESC : Back"
    );
    FloatRect h = menuText.getLocalBounds();
        menuText.setOrigin(h.width / 2, h.height / 2);
        menuText.setPosition(320 / 2, 240);
        window.draw(menuText);
        window.display();
    continue;
    }
    if (currentState == STATE_PAUSE) {
        window.clear();
        window.draw(background);
        menuText.setString(
        "PAUSED\n\n"
        "1. Start New Game\n"
        "3. Help\n"
        "4. Exit\n"
        "5. Continue"
    );
    FloatRect p = menuText.getLocalBounds();
    menuText.setOrigin(p.width / 2, p.height / 2);
    menuText.setPosition(320 / 2, 240);
    window.draw(menuText);
    window.display();
    continue;
    }

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        movePiece(delta_x);
        if (rotate)
            rotatePiece();
        if (gameOver)
        {
            // Add current score
            highScores[9] = score;

            // Sort descending
            std::sort(highScores, highScores + 10, std::greater<int>());

            // Save back to file
            saveHighScores();

            // Update score text
            finalScoreText.setString("Score: " + std::to_string(score));

            // Center align score text
            FloatRect scBounds = finalScoreText.getLocalBounds();
            finalScoreText.setOrigin(scBounds.width / 2, scBounds.height / 2);
            finalScoreText.setPosition(320 / 2, 480 / 2 + 20);
            window.clear();
            window.draw(background);
            window.draw(frame);
            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.draw(restartText);
            window.display();
            continue;   // 🔥 VERY IMPORTANT
        }

            fallingPiece(timer, delay);

        delta_x = 0;
        rotate = false;
        delay = 0.3;
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        ///////////////////////////////////////////////
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(); // Changing
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18 + 1, i*18 + 1);
                sprite.move(70, 41); // centered horizontally
                window.draw(sprite);
            }
        }
        int shadow[4][2];
            for (int i=0;i<4;i++)
            {
                shadow[i][0] = point_1[i][0];
                shadow[i][1] = point_1[i][1];
            }

            while (true)
            {
                bool stop=false;
                for (int i=0;i<4;i++)
                    if (shadow[i][1]+1 >= M || gameGrid[shadow[i][1]+1][shadow[i][0]])
                        stop=true;

                if (stop) break;
                for (int i=0;i<4;i++)
                    shadow[i][1]++;
            }

            sprite.setColor(Color(255,255,255,80));
            for (int i=0;i<4;i++)
            {
                sprite.setPosition(shadow[i][0]*18+1, shadow[i][1]*18+1);
                sprite.move(70, 41); // centered horizontally
                window.draw(sprite);
            }
            sprite.setColor(Color::White);

        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18 + 1, point_1[i][1]*18 + 1);
            sprite.move(70, 41); // centered horizontally
            window.draw(sprite);
          }

        //---The Final on Which Everything is Drawn Over is Loaded---//
        //window.draw(finalScoreText);
        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);
        // 🔹 HIGH SCORES PANEL (RIGHT SIDE – ALWAYS VISIBLE)
        window.draw(hsTitle);

        for (int i = 0; i < 10; i++)
        {
            // 🔹 Highlight current score if game over
            if (gameOver && highScores[i] == score)
                highScoreText.setFillColor(Color::Yellow);
            else
                highScoreText.setFillColor(Color::White);

            highScoreText.setString(
                std::to_string(i + 1) + ". " + std::to_string(highScores[i])
            );

            highScoreText.setPosition(HS_X, 110 + i * 18);
            window.draw(highScoreText);
        }
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
