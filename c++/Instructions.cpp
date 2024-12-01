#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void startGame(); // 게임 시작 함수

void showDescription() {
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임 방법.png")) {
        return;
    }
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;
    }

    sf::RectangleShape startButton(sf::Vector2f(250, 60));
    startButton.setFillColor(sf::Color(92, 112, 94));
    startButton.setPosition(340, 600);

    sf::Text startButtonText(L"게임 시작", font, 40);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(390, 605);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();
                        startGame();
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(startButton);
        window.draw(startButtonText);
        window.display();
    }
}
