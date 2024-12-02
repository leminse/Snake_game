#include <SFML/Graphics.hpp>                   
#include <random>     
#include <string>
#include <deque>				//�����̳ʸ� ����� ���� ���� ����

const float Snake_Speed = 25.f;			// �⺻ �� �̵� �ӵ�
const sf::Vector2f GRID_SIZE(25.f, 25.f); // �׸��� ũ�� (�� �� ���� ������ ���� ����) 25 * 25 �ȼ� ũ��
/*�׸����, ���� ȭ���� ���� �簢����� ������ �� ��ü(��, ���� ��)��
��Ȯ�� �ش� �簢���� ��輱�� ���� ��ġ�ǵ��� �����ϴ� ����� �ǹ� */
const int width = 906;					// ���� ȭ���� �ʺ� 
const int height = 795;					// ���� ȭ���� ����

//���� ������ ��Ÿ���� ������
enum Movement { STOP = 0, UP, DOWN, LEFT, RIGHT };

//���� ����ü
struct Prey {
    sf::Sprite sprite;			//���̸� ��Ÿ���� ��������Ʈ
    std::string type;			//���� Ÿ�� (���, ���Ƹ�, ��)
};

//���� ���� ��ġ ����
sf::Vector2f RandomPosition() {
    std::random_device rd;           // �ϵ���� ���� ������ �ʱ�ȭ
    std::mt19937 gen(rd());          // Mersenne Twister ���� ���
    std::uniform_int_distribution<int> xDist(0, (width / (int)GRID_SIZE.x) - 1);
    // x��ǥ: �׸��� ũ�⸦ �������� ���� ���� �� ����
    std::uniform_int_distribution<int> yDist(0, (height / (int)GRID_SIZE.y) - 1);
    // y��ǥ: �׸��� ũ�⸦ �������� ���� ���� �� ����
    return sf::Vector2f(xDist(gen) * GRID_SIZE.x, yDist(gen) * GRID_SIZE.y);
    // ������ x, y ��ġ�� ��ȯ (�׸��� ���� ����)
}

void startGame() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");
    // RenderWindow ����: �־��� ũ��� �������� ���� â ����
    window.setFramerateLimit(60);
    // ������ �ӵ� ����: ������ �ʴ� 60 ���������� �����ϵ��� ����

    // ��Ʈ �ε� �� ����
    sf::Font font;  // ��Ʈ ��ü ����
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {  // ��Ʈ ���� �ε�
        return;  // ��Ʈ �ε� ���� �� �Լ� ����
    }


    sf::Texture backgroundTexture, snakeHeadTexture, snakeBodyTexture, appleTexture, chickTexture, mouseTexture;
    backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/����â.png");   // ��� �ؽ�ó �ε�
    snakeHeadTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/�� �Ӹ�.png");  // �� �Ӹ� �ؽ�ó �ε�
    snakeBodyTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/�첿��.png");  // �� ���� �ؽ�ó �ε�
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���.png");         // ��� �ؽ�ó �ε�
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���Ƹ�.png");       // ���Ƹ� �ؽ�ó �ε�
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/��.png");             // �� �ؽ�ó �ε�

    sf::Sprite background(backgroundTexture);				// ��� ��������Ʈ ����
    sf::Sprite snakeHead(snakeHeadTexture);					// �� �Ӹ� ��������Ʈ ����
    snakeHead.setPosition(width / 2.f, height / 2.f);		// �� �Ӹ� ��ġ - �߾�

    std::deque<sf::Sprite> snakeBody;  // ���� ������ ������ deque �����̳�
    Movement direction = STOP;       // ���� �ʱ� �̵� ����
    Movement nextDirection = direction; // ����ڰ� ������ ���� ����

    float speed = Snake_Speed;	  // ���� ���� �̵� �ӵ� (�⺻ �ӵ��� ����)
    float timer = 0.f;			  // �̵� Ÿ�̸� �ʱ�ȭ
    sf::Clock clock;			  // SFML Clock ��ü�� �ð� ����
    bool gameover = false;		  // ���� ���� �÷��� �ʱ�ȭ
    int score = 0;				  // ���� ���� �ʱ�ȭ

    Prey prey;									// prey ����ü ����
    prey.sprite.setTexture(appleTexture);		// �ʱ� ���� Ÿ���� "apple"
    prey.type = "apple";
    prey.sprite.setPosition(RandomPosition());  // ������ ��ġ�� ��ġ

    while (window.isOpen()) {
        // window.isOpen(): ���� â�� ���� �ִ��� Ȯ��
        sf::Event event;
        // SFML �̺�Ʈ ��ü: Ű����, ���콺 �� â �̺�Ʈ ó��
        while (window.pollEvent(event)) {
            // �̺�Ʈ ���� ����: �̺�Ʈ ť���� �̺�Ʈ�� �ϳ��� ������. ť�� �̺�Ʈ�� ���� �� ó��
            if (event.type == sf::Event::Closed)
                // â �ݱ� �̺�Ʈ�� �߻��ϸ�
                window.close();  // â ����

            // ���� �Է� 
            if (event.type == sf::Event::KeyPressed) {
                // Ű�� ������ �� �̺�Ʈ
                if (event.key.code == sf::Keyboard::W && direction != DOWN) nextDirection = UP;
                if (event.key.code == sf::Keyboard::S && direction != UP) nextDirection = DOWN;
                if (event.key.code == sf::Keyboard::A && direction != RIGHT) nextDirection = LEFT;
                if (event.key.code == sf::Keyboard::D && direction != LEFT) nextDirection = RIGHT;
                // W, A, S, D Ű �Է����� ���� ��ȯ
                // �ݴ� ���������� ��ȯ ���� (ex: UP -> DOWN �Ұ�)
            }
        }

        direction = nextDirection;  // ������ �̵��� ���� ����

        // ���� �Ӹ� ��ġ ������Ʈ
        sf::Vector2f nextPosition = snakeHead.getPosition();
        if (direction == UP) nextPosition.y -= GRID_SIZE.y;   // ���� �̵�
        if (direction == DOWN) nextPosition.y += GRID_SIZE.y; // �Ʒ��� �̵�
        if (direction == LEFT) nextPosition.x -= GRID_SIZE.x; // �������� �̵�
        if (direction == RIGHT) nextPosition.x += GRID_SIZE.x; // ���������� �̵�

        // �� �Ӹ� ��ġ ������Ʈ
        snakeHead.setPosition(nextPosition);  // ���� ���ο� ��ġ�� �� �Ӹ� �̵�

        // ���̿��� �浹 üũ
        if (snakeHead.getGlobalBounds().intersects(prey.sprite.getGlobalBounds())) {
            // �� �Ӹ��� ������ �浹�� �˻�
            if (prey.type == "apple") {  // ��� ���̸� ������
                score += 1;  // ���� ����
                sf::Sprite newSegment(snakeBodyTexture);  // ���ο� ���� ����
                if (!snakeBody.empty()) newSegment.setPosition(snakeBody.back().getPosition());  // ���� �ڿ� ��ġ
                else newSegment.setPosition(snakeHead.getPosition());  // ó���� �Ӹ� ��ġ�� ���� �߰�
                snakeBody.push_back(newSegment);  // �� ���뿡 ���� ������ ���� �߰�
            }
            else if (prey.type == "chick") {  // ���Ƹ� ���̸� ������
                score += 1;  // ���� ����
            }
            else if (prey.type == "mouse") {  // �� ���̸� ������
                score += 2;  // ���� 2�� ����
                sf::Sprite newSegment(snakeBodyTexture);  // ���ο� ���� ����
                if (!snakeBody.empty()) newSegment.setPosition(snakeBody.back().getPosition());  // ���� �ڿ� ��ġ
                else newSegment.setPosition(snakeHead.getPosition());  // ó���� �Ӹ� ��ġ�� ���� �߰�
                snakeBody.push_back(newSegment);  // �� ���뿡 ���� ������ ���� �߰�
            }
        }

        // ���ο� ���� ���� ��ġ�� ����
        prey.sprite.setPosition(RandomPosition());  // �� ��ġ�� ���� ��ġ
        int preyType = rand() % 3;  // �������� ���� ���� ����

        if (preyType == 0) {
            prey.sprite.setTexture(appleTexture);  // ���
            prey.type = "apple";
        }
        else if (preyType == 1) {
            prey.sprite.setTexture(chickTexture);  // ���Ƹ�
            prey.type = "chick";
        }
        else {
            prey.sprite.setTexture(mouseTexture);  // ��
            prey.type = "mouse";
        }
        // ���� ȭ�� �׸���
        window.clear();  // ȭ�� �ʱ�ȭ
        window.draw(background);  // ��� �׸���
        for (const auto& segment : snakeBody) window.draw(segment);  // �� ���� �׸���
        window.draw(snakeHead);  // �� �Ӹ� �׸���
        window.draw(prey.sprite);  // ���� �׸���
        window.display();  // ȭ�鿡 ��� ��ü ���
    }
}