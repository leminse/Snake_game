#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>    

int main() {
    // â ũ�� ����: 800x600 ũ���� ������ â ����, â ���� : Snake Game
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // ��� �̹��� �ε�
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/ó��ȭ��.png")) {
        return -1;  // ��� �̹��� ������ ã�� ���ϸ� ���α׷� ����
    }
    
    sf::Sprite backgroundSprite(backgroundTexture);  // ��������Ʈ�� ��ȯ�Ͽ� ȭ�鿡 ���

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;  // ��Ʈ ������ ã�� ���ϸ� ���α׷� ����
    }

    // Play ��ư
    sf::Text playButton("Play", font, 30);                  // ��Ʈ, ũ�� 30
    playButton.setPosition(270, 270);                       // "Play" ��ư�� ��ġ ���� (x=350, y=300)
    playButton.setFillColor(sf::Color::Black);              // �ؽ�Ʈ ������ ���������� ����

    // ���� ��� ��ư 
    sf::Text instructionsButton(L"���� ���", font, 30);     // ��Ʈ, ũ�� 30
    instructionsButton.setPosition(270, 340);               // "���� ���" ��ư�� ��ġ ���� (x=300, y=400)
    instructionsButton.setFillColor(sf::Color::Black    );      // �ؽ�Ʈ ������ ���������� ����

    // â�� ���� �ִ� ���� ����Ǵ� ����
    while (window.isOpen()) {
        sf::Event event;
        // �̺�Ʈ�� �߻��ߴ��� Ȯ���ϴ� ����
        while (window.pollEvent(event)) {
            // â�� �ݴ� �̺�Ʈ�� �߻��ϸ� â�� ����
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ȭ���� ���� �׸��� ���� ��� �̹��� �׸���
        window.clear();  // ����� ���� ��

        // ��� �̹����� ȭ�鿡 �׸���
        window.draw(backgroundSprite);
        
        // �ؽ�Ʈ �� ��ư�� â�� �׸���
        window.draw(playButton);           // Play ��ư
        window.draw(instructionsButton);   // ���� ��� ��ư

        // ȭ�鿡 �׸� ��� ���� ���
        window.display();
    }

    return 0;  // ���α׷� ����
}
