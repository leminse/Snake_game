#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// �ܺο� ���ǵ� �Լ� ���� (������ ���� game.cpp, instructions.cpp�� ����)
void startGame();         // ���� ���� �Լ�
void showDescription();   // ���� ���� �Լ�

int main() {
    // â ũ�� ����: 606x495 ũ���� ������ â ����, ����: Snake Game
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    // ��� �̹��� �ε� �� �ؽ�ó ����
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/ó��ȭ��.png")) {
        return -1;  // ��� �̹��� ������ ã�� ���ϸ� ���α׷� ����
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // ��� �̹����� ��������Ʈ�� ��ȯ

    // ��Ʈ �ε� �� ����
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;  // ��Ʈ ������ ã�� ���ϸ� ���α׷� ����
    }

    // ���� ��ư ����: ũ��, ����, ��ġ ����
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(92, 112, 94));  // ��� �迭
    startButton.setPosition(500, 570);                // (x, y) ��ġ

    // ���� ��ư �ؽ�Ʈ ���� �� ����
    sf::Text startButtonText(L"���� ����", font, 30);
    startButtonText.setFillColor(sf::Color::White);  // �Ͼ�� �ؽ�Ʈ
    startButtonText.setPosition(545, 577);          // �ؽ�Ʈ ��ġ ����

    // ���� ���� ��ư ����: ũ��, ����, ��ġ ����
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(92, 112, 94));  // ��� �迭
    instructionsButton.setPosition(500, 634);                // (x, y) ��ġ

    // ���� ���� ��ư �ؽ�Ʈ ���� �� ����
    sf::Text instructionsButtonText(L"���� ���", font, 30);
    instructionsButtonText.setFillColor(sf::Color::White);  // �Ͼ�� �ؽ�Ʈ
    instructionsButtonText.setPosition(545, 641);          // �ؽ�Ʈ ��ġ ����

    // â�� ���� �ִ� ���� ����Ǵ� ���� ����
    while (window.isOpen()) {
        sf::Event event;  // �̺�Ʈ ��ü ����
        while (window.pollEvent(event)) {  // �̺�Ʈ ó��
            if (event.type == sf::Event::Closed)  // â �ݱ� �̺�Ʈ
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {  // ���콺 Ŭ�� �̺�Ʈ
                if (event.mouseButton.button == sf::Mouse::Left) {  // ���� ��ư Ŭ��
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // ���콺 ��ǥ ��������

                    // ���� ��ư Ŭ�� ó��
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  // ���� â �ݱ�
                        startGame();     // �ܺ� �Լ� ȣ�� (���� ����)
                    }

                    // ���� ���� ��ư Ŭ�� ó��
                    if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();        // ���� â �ݱ�
                        showDescription();     // �ܺ� �Լ� ȣ�� (���� ���� ǥ��)
                    }
                }
            }
        }

        // ȭ�� �׸���
        window.clear();                       // ���� ȭ�� �����
        window.draw(backgroundSprite);        // ��� �̹��� �׸���
        window.draw(startButton);             // ���� ��ư �׸���
        window.draw(startButtonText);         // ���� ��ư �ؽ�Ʈ �׸���
        window.draw(instructionsButton);      // ���� ���� ��ư �׸���
        window.draw(instructionsButtonText);  // ���� ���� ��ư �ؽ�Ʈ �׸���
        window.display();                     // ���� �׸� ȭ���� ���÷���
    }

    return 0;  // ���α׷� ���� ����
}
