#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <ctime>

void main();

const int width = 906;
const int height = 795;
const int GRID_SIZE = 20;
const float Snake_Speed = 10.f;
const float Chick_Speed = 12.f;
const float Mouse_Speed = 8.f;

enum Movement { STOP = 0, UP, DOWN, LEFT, RIGHT };

struct Prey {
    sf::Sprite sprite;
    std::string type;
};

sf::Vector2f RandomPosition() {
    int x = rand() % (width / GRID_SIZE) * GRID_SIZE;
    int y = rand() % (height / GRID_SIZE) * GRID_SIZE;
    return sf::Vector2f(x, y);
}

void startGame() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;
    }

    sf::Texture backgroundTexture, snakeHead_rightTexture, snakeHead_leftTexture, snakeHead_upTexture, snakeHead_downTexture, snakeBody_verticalTexture, snakeBody_horizontalTexture, appleTexture, chickTexture, mouseTexture;
    backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/°ÔÀÓÃ¢.png");
    snakeHead_rightTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸Ó¸®_¿À.png");
    snakeHead_leftTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸Ó¸®_¿Þ.png");
    snakeHead_upTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸Ó¸®_À§.png");
    snakeHead_downTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸Ó¸®_¾Æ·¡.png");
    snakeBody_verticalTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸öÅë_¼¼·Î.png");
    snakeBody_horizontalTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/¹ì ¸öÅë_°¡·Î.png");
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/»ç°ú.png");
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/º´¾Æ¸®.png");
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/Áã.png");

    sf::Sprite background(backgroundTexture);
    sf::Sprite snakeHead(snakeHead_rightTexture);
    snakeHead.setPosition(width / 2.f, height / 2.f);

    std::deque<sf::Sprite> snakeBody;
    Movement direction = STOP;
    Movement nextDirection = direction;

    float speed = Snake_Speed;
    float timer = 0.f;
    sf::Clock clock;
    bool gameover = false;
    int score = 0;
    float effectTimer = 0.f;

    Prey prey;
    prey.sprite.setTexture(appleTexture);
    prey.type = "apple";
    prey.sprite.setPosition(RandomPosition());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W && direction != DOWN) nextDirection = UP;
                if (event.key.code == sf::Keyboard::S && direction != UP) nextDirection = DOWN;
                if (event.key.code == sf::Keyboard::A && direction != RIGHT) nextDirection = LEFT;
                if (event.key.code == sf::Keyboard::D && direction != LEFT) nextDirection = RIGHT;
            }
        }

        if (gameover) {
            window.clear();
            sf::Text gameOverText("Game Over!", font, 40);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(width / 2.f - 100, 360);

            sf::Text gameOverScoreText("score : " + std::to_string(score), font, 40);
            gameOverScoreText.setFillColor(sf::Color::White);
            gameOverScoreText.setPosition(width / 2.f - 100, 300);

            sf::RectangleShape homeButton(sf::Vector2f(250, 60));
            homeButton.setFillColor(sf::Color(92, 112, 94));
            homeButton.setPosition(340, 554);

            sf::Text homeButtonText(L"Ã³À½À¸·Î", font, 40);
            homeButtonText.setFillColor(sf::Color::White);
            homeButtonText.setPosition(390, 561);

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (homeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        main();
                    }
                }
            }

            window.draw(gameOverText);
            window.draw(gameOverScoreText);
            window.draw(homeButton);
            window.draw(homeButtonText);
            window.display();
            continue;
        }

        float deltaTime = clock.restart().asSeconds();
        timer += deltaTime;
        if (effectTimer > 0.f) effectTimer -= deltaTime;

        if (timer > 1.f / speed) {
            timer = 0.f;

            direction = nextDirection;
            sf::Vector2f nextPosition = snakeHead.getPosition();

            if (direction == UP) {
                nextPosition.y -= GRID_SIZE;
                snakeHead.setTexture(snakeHead_upTexture);  // ¸Ó¸® ÅØ½ºÃ³ º¯°æ
            }
            if (direction == DOWN) {
                nextPosition.y += GRID_SIZE;
                snakeHead.setTexture(snakeHead_downTexture);  // ¸Ó¸® ÅØ½ºÃ³ º¯°æ
            }
            if (direction == LEFT) {
                nextPosition.x -= GRID_SIZE;
                snakeHead.setTexture(snakeHead_leftTexture);  // ¸Ó¸® ÅØ½ºÃ³ º¯°æ
            }
            if (direction == RIGHT) {
                nextPosition.x += GRID_SIZE;
                snakeHead.setTexture(snakeHead_rightTexture);  // ¸Ó¸® ÅØ½ºÃ³ º¯°æ
            }

            if (nextPosition.x < 0 || nextPosition.x >= width || nextPosition.y < 0 || nextPosition.y >= height) {
                gameover = true;
                continue;
            }

            for (const auto& segment : snakeBody) {
                if (segment.getPosition() == nextPosition) {
                    gameover = true;
                    continue;
                }
            }

            if (!snakeBody.empty()) {
                snakeBody.push_front(snakeHead);
                snakeBody.pop_back();
            }

            snakeHead.setPosition(nextPosition);

            if (snakeHead.getGlobalBounds().intersects(prey.sprite.getGlobalBounds())) {
                if (prey.type == "apple") {
                    score += 1;
                    sf::Sprite newSegment(snakeBody_horizontalTexture);  // »ç°ú¸¦ ¸ÔÀ¸¸é °¡·Î ¸öÅë Ãß°¡
                    if (!snakeBody.empty()) newSegment.setPosition(snakeBody.back().getPosition());
                    else newSegment.setPosition(snakeHead.getPosition());
                    snakeBody.push_back(newSegment);
                }
                else if (prey.type == "chick") {
                    score += 1;
                    if (!snakeBody.empty()) snakeBody.pop_back();
                    speed = Chick_Speed;
                    effectTimer = 3.f;
                }
                else if (prey.type == "mouse") {
                    score += 2;
                    sf::Sprite newSegment1(snakeBody_verticalTexture), newSegment2(snakeBody_verticalTexture);
                    if (!snakeBody.empty()) {
                        newSegment1.setPosition(snakeBody.back().getPosition());
                        newSegment2.setPosition(snakeBody.back().getPosition());
                    }
                    else {
                        newSegment1.setPosition(snakeHead.getPosition());
                        newSegment2.setPosition(snakeHead.getPosition());
                    }
                    snakeBody.push_back(newSegment1);
                    snakeBody.push_back(newSegment2);
                    speed = Mouse_Speed;
                    effectTimer = 3.f;
                }

                prey.sprite.setPosition(RandomPosition());
                int preyType = rand() % 3;

                if (preyType == 0) {
                    prey.sprite.setTexture(appleTexture);
                    prey.type = "apple";
                }
                else if (preyType == 1) {
                    prey.sprite.setTexture(chickTexture);
                    prey.type = "chick";
                }
                else {
                    prey.sprite.setTexture(mouseTexture);
                    prey.type = "mouse";
                }
            }

            if (effectTimer <= 0.f) speed = Snake_Speed;
        }

        window.clear();
        window.draw(background);
        for (const auto& segment : snakeBody) window.draw(segment);
        window.draw(snakeHead);
        window.draw(prey.sprite);
        window.display();
    }

    return;
}
