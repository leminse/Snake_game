#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>    

int main() {
    // 창 크기 설정: 800x600 크기의 윈도우 창 생성, 창 제목 : Snake Game
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // 배경 이미지 로드
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/처음화면.png")) {
        return -1;  // 배경 이미지 파일을 찾지 못하면 프로그램 종료
    }
    
    sf::Sprite backgroundSprite(backgroundTexture);  // 스프라이트로 변환하여 화면에 출력

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;  // 폰트 파일을 찾지 못하면 프로그램 종료
    }

    // Play 버튼
    sf::Text playButton("Play", font, 30);                  // 폰트, 크기 30
    playButton.setPosition(270, 270);                       // "Play" 버튼의 위치 설정 (x=350, y=300)
    playButton.setFillColor(sf::Color::Black);              // 텍스트 색상을 검정색으로 설정

    // 게임 방법 버튼 
    sf::Text instructionsButton(L"게임 방법", font, 30);     // 폰트, 크기 30
    instructionsButton.setPosition(270, 340);               // "게임 방법" 버튼의 위치 설정 (x=300, y=400)
    instructionsButton.setFillColor(sf::Color::Black    );      // 텍스트 색상을 검정색으로 설정

    // 창이 열려 있는 동안 실행되는 루프
    while (window.isOpen()) {
        sf::Event event;
        // 이벤트가 발생했는지 확인하는 루프
        while (window.pollEvent(event)) {
            // 창을 닫는 이벤트가 발생하면 창을 닫음
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 화면을 새로 그리기 전에 배경 이미지 그리기
        window.clear();  // 배경을 지운 후

        // 배경 이미지를 화면에 그리기
        window.draw(backgroundSprite);
        
        // 텍스트 및 버튼을 창에 그리기
        window.draw(playButton);           // Play 버튼
        window.draw(instructionsButton);   // 게임 방법 버튼

        // 화면에 그린 모든 것을 출력
        window.display();
    }

    return 0;  // 프로그램 종료
}
