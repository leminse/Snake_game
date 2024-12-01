#include <SFML/Graphics.hpp>   // SFML�� �׷��� ����� ����ϱ� ���� ��� ����
#include <SFML/Window.hpp>     // SFML�� ������ ����� ����ϱ� ���� ��� ����
#include <vector>               // ���͸� ����ϱ� ���� ��� ����
#include <random>               // ���� ������ ���� ��� ����

void startGame() {

    // ���� â ũ��� ���� ����
    const int tileSize = 20;    // �� Ÿ���� ũ�� (20x20 �ȼ�)
    const int width = 45;       // ���� ȭ���� �ʺ� (Ÿ���� ��)
    const int height = 40;      // ���� ȭ���� ���� (Ÿ���� ��)
    sf::RenderWindow window(sf::VideoMode(width * tileSize, height * tileSize), "Snake Game");  // ���� â ����
    //VideoMode�� 45 * 20, 40 * 20 ������.

    // ��� �̹��� �ε� �� �ؽ�ó ����
    sf::Texture backgroundTexture;   // ����� ���� �ؽ�ó ��ü
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/����â.png")) {  // ��� �̹��� ���� �ε�
        return;  // �̹��� �ε� ���� �� �Լ� ����
    }
    sf::Sprite backgroundSprite(backgroundTexture);   // ��� �̹����� ǥ���� ��������Ʈ ��ü ����

    // ��Ʈ �ε� �� ����
    sf::Font font;  // ��Ʈ ��ü ����
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {  // ��Ʈ ���� �ε�
        return;  // ��Ʈ �ε� ���� �� �Լ� ����
    }

    //���� ��ü �ʱ�ȭ
    bool gameover = false;              //���� ����
    int x = width / 2, y = height / 2;   // ���� �ʱ� ��ġ - �߾�
    int preyX, preyY;                       //���� ��ġ
    int score = 0;                          //����
    std::vector<sf::Vector2f> tail;            //���� �������� �ε巴�� �ϱ� ���� Vector2f�� ���. (�Ǽ�)
    // ���� ���� (���� ��ġ ��Ͽ� ����)
    enum Movement { STOP = 0, LEFT, RIGHT, UP, DOWN };          //����, ����, ������, ��, �Ʒ�
    Movement beginning = STOP;                      //���� ó�� ���� = ����

    std::random_device ra;                          //���� ���� ��ġ
    std::mt19937 ge(ra());                          // Mersenne Twister �˰����� ����� ���� ������
    std::uniform_int_distribution<> dis(0, width - 1);
    preyX = dis(ge);                                    //������ ��ġ�� ���� ����
    preyY = dis(ge);                                    //������ ��ġ�� ���� ����

    // ���� ȭ�� �׸���� Ÿ�� ����
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    // RectangleShape: ���簢�� ����� �׸��� ���� Ŭ����

    sf::Texture appleTexture;
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���.png");

    sf::Texture chickTexture;
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���Ƹ�.png");

    sf::Texture mouseTexture;
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/��.png");

    sf::Texture snakeHeadTexture;
    snakeHeadTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/�� �Ӹ�.png");

    sf::Texture snakeTailTexture;
    snakeTailTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/�� ����.png");

    sf::Sprite preySprite;   // ���̸� �׸� ��������Ʈ ��ü

    sf::Sprite snakeHeadSprite(snakeHeadTexture);   // �� �Ӹ�

    sf::Sprite snakeTailSprite(snakeTailTexture);   // �� ����

    // �ӵ��� �����ϱ� ���� sf::Clock ���
    sf::Clock clock;
    // sf::Clock�� �ð� ������ ���� Ŭ����. 
    float MoveSpeed = 0.3f;
    // ���� �̵� �ӵ��� �� ������ ����. �������� �� ������ ������.
    float lastMoveTime = 0.f;
    // ���������� ���� ������ �ð��� ����.
    bool speedUp = false;  // �ӵ� ���� ����
    bool slowDown = false;  // �ӵ� ���� ����
    float speedChangeTime = 0.f;  // �ӵ� ��ȭ �ð�
    int lengthChange = 0;  // ���� ��ȭ �� (���� ������ ���� �ٸ�)

    // ���� ���� ����
    while (window.isOpen()) {
        // window.isOpen(): ���� â�� ���� �ִ��� Ȯ���մϴ�.
        sf::Event event;
        while (window.pollEvent(event)) {
            // �̺�Ʈ ť���� �̺�Ʈ�� �ϳ��� �����ɴϴ�.
            if (event.type == sf::Event::Closed) {
                // â �ݱ� �̺�Ʈ�� �߻��ϸ�
                window.close();  // â�� �ݽ��ϴ�.
            }
        }

        if (!gameover) {
            // ���� ���� ���°� �ƴ϶�� ����
            float deltaTime = clock.restart().asSeconds();
            // clock.restart(): �ð踦 �缳���ϰ�, ���� ���������� ��� �ð��� �� ������ ��ȯ.
            if (deltaTime + lastMoveTime >= MoveSpeed) {
                // deltaTime(��� �ð�)�� lastMoveTime(������ �̵� �ð��� ��)�� moveSpeed���� ũ��
                lastMoveTime = deltaTime;
                // lastMoveTime�� deltaTime���� ������Ʈ�Ͽ� ���� �̵� ������ ����

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && beginning != RIGHT) beginning = LEFT;   // ���� ����Ű
                // ���� ȭ��ǥ Ű�� ������ dir�� LEFT�� ����
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && beginning != LEFT) beginning = RIGHT;   // ������ ����Ű
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && beginning != DOWN) beginning = UP;   // �� ����Ű
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && beginning != UP) beginning = DOWN;   // �Ʒ� ����Ű

                sf::Vector2f prev(x, y);   // �� �Ӹ��� ���� ��ġ ����
                sf::Vector2f prev2;  // ������ ���� ��ġ ����� �ӽ� ����
                for (size_t i = 0; i < tail.size(); i++) {   // ���� �κ� �̵�
                    //size_t : �����̳��� ũ�⳪ �迭�� ũ�� �� ���������� �ٷ� �� ������ ����.
                    // ������ �� �κ��� ������Ʈ
                    prev2 = tail[i];
                    tail[i] = prev;
                    prev = prev2;
                }

                // �̵� ���⿡ ���� �� �Ӹ� ��ġ ������Ʈ
                switch (beginning) {
                case LEFT: x--; break;
                case RIGHT: x++; break;
                case UP: y--; break;
                case DOWN: y++; break;
                default: break;
                }

                // ���� ������ ���� ����
                if (x < 0 || x >= width || y < 0 || y >= height) {
                    // x�� 0���� �۰ų� width �̻�, �Ǵ� y�� 0���� �۰ų� height �̻��̸�
                    gameover = true;  // ���� ���� ���·� ����
                }

                // ���� �ڱ� ������ ������ ���� ����
                for (auto& segment : tail) {
                    if (segment.x == x && segment.y == y) {
                        // ���� ���� �Ӹ� ��ġ�� ������ ��� �κа� �����ϸ�
                        gameover = true;  // ���� ���� ���·� ����
                    }
                }
                window.clear();  // ȭ���� �����

                window.draw(backgroundSprite);  // ����� �׸���

                snakeHeadSprite.setPosition(x * tileSize, y * tileSize);  // �� �Ӹ� ��ġ ����
                window.draw(snakeHeadSprite);  // �� �Ӹ� �׸���

                sf::Text scoreText;
                scoreText.setFont(font);  // ���� �ؽ�Ʈ�� ��Ʈ ����
                scoreText.setString("Score: " + std::to_string(score));  // ���� �ؽ�Ʈ ����
                scoreText.setCharacterSize(24);  // �ؽ�Ʈ ũ�� ����
                scoreText.setFillColor(sf::Color::White);  // �ؽ�Ʈ ���� ����
                scoreText.setPosition(10, 10);  // �ؽ�Ʈ ��ġ ����
                window.draw(scoreText);  // ���� �ؽ�Ʈ �׸���

                window.display();  // ȭ���� �����Ѵ�
            }
        }
    }