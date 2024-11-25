#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void startGame() {
    // 창 크기 및 제목 설정
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // 배경 이미지 로드 및 텍스처 설정
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임창.png")) {
        return;  // 배경 이미지 파일을 찾지 못하면 프로그램 종료
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // 배경 이미지를 스프라이트로 변환

    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // 폰트 로드 실패 시 함수 종료
    }

    // 이벤트 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    // 화면 그리기
    window.clear();                       // 이전 화면 지우기
    window.draw(backgroundSprite);        // 배경 이미지 그리기
    window.display();                     // 디스플레이 업데이트
}