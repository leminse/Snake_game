#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>

void main();


// ���� ���� ������ �����ϴ� �Լ�
void startGame() {
    // ���� â ũ��� ���� ����
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    // ��� �̹��� �ε� �� �ؽ�ó ����
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/����â.png")) {
        return;  // ��� �̹��� ������ ã�� ���ϸ� ���α׷� ����
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // ��� �̹����� ��������Ʈ�� ��ȯ

    // ��Ʈ �ε� �� ����
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // ��Ʈ ������ ã�� ���ϸ� ���α׷� ����
    }

    // ���� ���� ���� �ʱ�ȭ
    const int width = 20;
    const int height = 15;
    const int tileSize = 30;
    bool gameOver = false;
    int x = width / 2, y = height / 2, fruitX, fruitY, score = 0;
    std::vector<sf::Vector2i> tail;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir = STOP;

    // ������ �ʱ� ��ġ ����
    fruitX = rand() % width;
    fruitY = rand() % height;

    // ���� ȭ�� �׸���
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize)); // �� Ÿ�� ũ�� ����
    sf::Texture appleTexture;
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���.png");
    sf::Texture chickTexture;
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���Ƹ�.png");
    sf::Texture mouseTexture;
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/��.png");
    sf::Sprite fruitSprite;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // ���� ���� �� �Է� ó��
        if (!gameOver) {
            // ����� �Է� (����Ű�� �� �̵�)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = LEFT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = RIGHT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = UP;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = DOWN;

            // �� �̵� �� ���� ����
            sf::Vector2i prev(x, y);
            sf::Vector2i prev2;
            for (size_t i = 0; i < tail.size(); i++) {
                prev2 = tail[i];
                tail[i] = prev;
                prev = prev2;
            }

            switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
            }

            // �� �浹 �˻�
            if (x < 0 || x >= width || y < 0 || y >= height) {
                gameOver = true;
            }

            // �ڱ� �ڽŰ� �浹 �˻�
            for (auto& segment : tail) {
                if (segment.x == x && segment.y == y) {
                    gameOver = true;
                }
            }

            // ���� �Ա� ó��
            if (x == fruitX && y == fruitY) {
                score += 1;
                tail.push_back(sf::Vector2i(x, y));
                fruitX = rand() % width;
                fruitY = rand() % height;
            }

            // ���� ȭ�� �׸���
            window.clear();

            // ��� �׸���
            window.draw(backgroundSprite);  // ����� ���� �׸���

            // �� �׸���
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    tile.setPosition(i * tileSize, j * tileSize);
                    tile.setFillColor(sf::Color(50, 50, 50));
                    window.draw(tile);
                }
            }

            // �� �Ӹ� �׸���
            tile.setPosition(x * tileSize, y * tileSize);
            tile.setFillColor(sf::Color::Green);
            window.draw(tile);

            // �� ���� �׸���
            for (auto& segment : tail) {
                tile.setPosition(segment.x * tileSize, segment.y * tileSize);
                tile.setFillColor(sf::Color(0, 128, 0));
                window.draw(tile);
            }

            // ���� �׸���
            fruitSprite.setTexture(appleTexture);
            fruitSprite.setPosition(fruitX * tileSize, fruitY * tileSize);
            window.draw(fruitSprite);

            // ���� ǥ��
            sf::Text scoreText("����: " + std::to_string(score), font, 20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);
            window.draw(scoreText);

            window.display();
        }
        else {
            window.clear();
            sf::Text gameOverText("Game Over! Final Score: " + std::to_string(score), font, 30);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(width * tileSize / 4, height * tileSize / 2);

            // ���� ��ư ����: ũ��, ����, ��ġ ����
            sf::RectangleShape firstButton(sf::Vector2f(200, 50));
            firstButton.setFillColor(sf::Color(92, 112, 94));  // ��� �迭
            firstButton.setPosition(500, 570);                // (x, y) ��ġ
            // ���� ��ư �ؽ�Ʈ ���� �� ����
            sf::Text firstButtonText(L"ó������", font, 30);
            firstButtonText.setFillColor(sf::Color::White);  // �Ͼ�� �ؽ�Ʈ
            firstButtonText.setPosition(545, 577);          // �ؽ�Ʈ ��ġ ����

            if (event.type == sf::Event::MouseButtonPressed) {  // ���콺 Ŭ�� �̺�Ʈ
                if (event.mouseButton.button == sf::Mouse::Left) {  // ���� ��ư Ŭ��
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // ���콺 ��ǥ ��������

                    // ���� ��ư Ŭ�� ó��
                    if (firstButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  // ���� â �ݱ�
                        main();     // �ܺ� �Լ� ȣ�� 
                    }
                }
            }
            window.draw(gameOverText);
            window.draw(firstButton);
            window.draw(firstButtonText);
            window.display();
        }
    }

}
