#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


void startGame();         // ���� ���� �Լ�
void showDescription();   // ���� ���� �Լ�

int main() {
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/ó�� ȭ��.png")) {
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);             // ����� �׸� ��������Ʈ ��ü

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;
    }
                    
    // ���� ��ư ����
    sf::RectangleShape startButton(sf::Vector2f(250, 60));          //��ư ũ��
    startButton.setFillColor(sf::Color(92, 112, 94));               //����
    startButton.setPosition(340, 470);                              //��ġ

    // ���� ��ư �ؽ�Ʈ
    sf::Text startButtonText(L"���� ����", font, 40);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(390, 475);

    // ���� ���� ��ư ����
    sf::RectangleShape instructionsButton(sf::Vector2f(250, 60));
    instructionsButton.setFillColor(sf::Color(92, 112, 94));
    instructionsButton.setPosition(340, 554);

    // ���� ���� ��ư �ؽ�Ʈ
    sf::Text instructionsButtonText(L"���� ���", font, 40);
    instructionsButtonText.setFillColor(sf::Color::White);
    instructionsButtonText.setPosition(390, 561);

    // ���� ����: â�� �����ִ� ���� �ݺ� ����
    while (window.isOpen()) {
        sf::Event event;                                        // �̺�Ʈ ��ü ����
        while (window.pollEvent(event)) {                       // �߻��� �̺�Ʈ�� ť���� ������ ó��
            if (event.type == sf::Event::Closed)
                window.close();                                 // â �ݱ� �̺�Ʈ �߻� �� â�� ����

            // ���콺 Ŭ�� �̺�Ʈ ó��
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // ���콺 ���� ��ư Ŭ��
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Ŭ���� ���콺 ��ġ ��������

                    // ���� ��ư Ŭ�� ���� Ȯ��
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close(); // â �ݱ�
                        startGame();    // ���� ���� �Լ� ȣ��
                    }

                    // ���� ���� ��ư Ŭ�� ���� Ȯ��
                    if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close(); // â �ݱ�
                        showDescription(); // ���� ���� �Լ� ȣ��
                    }
                }
            }
        }

        // ȭ�� �׸���
        window.clear();                   // â�� ������ ����
        window.draw(backgroundSprite);    // ��� �̹��� �׸���
        window.draw(startButton);         // ���� ��ư �׸���
        window.draw(startButtonText);     // ���� ��ư �ؽ�Ʈ �׸���
        window.draw(instructionsButton);  // ���� ��ư �׸���
        window.draw(instructionsButtonText); // ���� ��ư �ؽ�Ʈ �׸���
        window.display();                 // ȭ�� ������Ʈ
    }

    return 0; // ���α׷� ����
}
