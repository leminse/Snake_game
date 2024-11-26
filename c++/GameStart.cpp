#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void startGame() {
    // â ũ�� �� ���� ����
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // ��� �̹��� �ε� �� �ؽ�ó ����
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/����â.png")) {
        return;  // ��� �̹��� ������ ã�� ���ϸ� ���α׷� ����
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // ��� �̹����� ��������Ʈ�� ��ȯ

    // ��Ʈ �ε�
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // ��Ʈ �ε� ���� �� �Լ� ����
    }

    // �̺�Ʈ ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 화면 그리기
        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    // ȭ�� �׸���
    window.clear();                       // ���� ȭ�� �����
    window.draw(backgroundSprite);        // ��� �̹��� �׸���
    window.display();                     // ���÷��� ������Ʈ
}