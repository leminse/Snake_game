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

        // ȭ���� ���� �׸��� ���� ��� �̹��� �׸���
        window.clear();  // ����� ���� ��

        // ��� �̹����� ȭ�鿡 �׸���
        window.draw(backgroundSprite);

        // ȭ�鿡 �׸� ��� ���� ���
        window.display();
        
        return 0;  // ���α׷� ����
    }

    
