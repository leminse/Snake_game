#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// 외부에 정의된 함수 선언. game.cpp에 존재
void startGame();           // 게임 시작 함수

void showDescription() {
    // 창 크기 및 제목 설정
    sf::RenderWindow window(sf::VideoMode(606, 495), "Snake Game");

    // 배경 이미지 로드 및 텍스처 설정
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임 방법.png")) {
        return;  // 배경 이미지 파일을 찾지 못하면 프로그램 종료
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // 배경 이미지를 스프라이트로 변환

    // 폰트 로드
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // 폰트 로드 실패 시 함수 종료
    }

    // 시작 버튼 생성: 크기, 색상, 위치 설정
    sf::RectangleShape startButton(sf::Vector2f(150, 50));
    startButton.setFillColor(sf::Color(92, 112, 94));  // 녹색 계열
    startButton.setPosition(360, 380);                // (x, y) 위치

    // 시작 버튼 텍스트 생성 및 설정
    sf::Text startButtonText(L"게임 시작", font, 26);
    startButtonText.setFillColor(sf::Color::White);  // 검은색 텍스트
    startButtonText.setPosition(388, 390);          // 텍스트 위치 조정

    // 이벤트 루프
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {  // 마우스 클릭 이벤트
                if (event.mouseButton.button == sf::Mouse::Left) {  // 왼쪽 버튼 클릭
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // 마우스 좌표 가져오기

                    // 시작 버튼 클릭 처리
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  // 현재 창 닫기
                        startGame();     // 외부 함수 호출 (게임 시작)
                    }
                }
            }
        }

        // 화면 그리기
        window.clear();                       // 이전 화면 지우기
        window.draw(backgroundSprite);        // 배경 이미지 그리기
        window.draw(startButton);             // 시작 버튼 그리기
        window.draw(startButtonText);         // 시작 버튼 텍스트 그리기
        window.display();                       // 디스플레이 업데이트
    }
}
