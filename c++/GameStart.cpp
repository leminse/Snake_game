#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void startGame() {
    // Ã¢ Å©±â ¹× Á¦¸ñ ¼³Á¤
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // ¹è°æ ÀÌ¹ÌÁö ·Îµå ¹× ÅØ½ºÃ³ ¼³Á¤
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/°ÔÀÓÃ¢.png")) {
        return;  // ¹è°æ ÀÌ¹ÌÁö ÆÄÀÏÀ» Ã£Áö ¸øÇÏ¸é ÇÁ·Î±×·¥ Á¾·á
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // ¹è°æ ÀÌ¹ÌÁö¸¦ ½ºÇÁ¶óÀÌÆ®·Î º¯È¯

    // ÆùÆ® ·Îµå
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // ÆùÆ® ·Îµå ½ÇÆĞ ½Ã ÇÔ¼ö Á¾·á
    }

    // ÀÌº¥Æ® ·çÇÁ
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // í™”ë©´ ê·¸ë¦¬ê¸°
        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    // È­¸é ±×¸®±â
    window.clear();                       // ÀÌÀü È­¸é Áö¿ì±â
    window.draw(backgroundSprite);        // ¹è°æ ÀÌ¹ÌÁö ±×¸®±â
    window.display();                     // µğ½ºÇÃ·¹ÀÌ ¾÷µ¥ÀÌÆ®
}