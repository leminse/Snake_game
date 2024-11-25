#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void showDescription() {
    // â ũ�� �� ���� ����
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // ��� �̹��� �ε� �� �ؽ�ó ����
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/���� ���.png")) {
        return;  // ��� �̹��� ������ ã�� ���ϸ� ���α׷� ����
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // ��� �̹����� ��������Ʈ�� ��ȯ

    // ��Ʈ �ε�
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // ��Ʈ �ε� ���� �� �Լ� ����
    }

    // ���� ��ư ����: ũ��, ����, ��ġ ����
    sf::RectangleShape startButton(sf::Vector2f(150, 50));
    startButton.setFillColor(sf::Color(92, 112, 94));  // ��� �迭
    startButton.setPosition(360, 380);                // (x, y) ��ġ

    // ���� ��ư �ؽ�Ʈ ���� �� ����
    sf::Text startButtonText(L"���� ����", font, 26);
    startButtonText.setFillColor(sf::Color::White);  // ������ �ؽ�Ʈ
    startButtonText.setPosition(388, 390);          // �ؽ�Ʈ ��ġ ����

    // �̺�Ʈ ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


    // ȭ�� �׸���
    window.clear();                       // ���� ȭ�� �����
    window.draw(backgroundSprite);        // ��� �̹��� �׸���
    window.draw(startButton);             // ���� ��ư �׸���
    window.draw(startButtonText);         // ���� ��ư �ؽ�Ʈ �׸���
    window.display();                       // ���÷��� ������Ʈ
    }   
}