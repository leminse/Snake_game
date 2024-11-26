#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// 외부에 정의된 함수 선언 (구현은 각각 game.cpp, instructions.cpp에 존재)
void startGame();         // 게임 시작 함수
void showDescription();   // 게임 설명 함수

int main() {
    // 창 크기 설정: 606x495 크기의 윈도우 창 생성, 제목: Snake Game
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    // 배경 이미지 로드 및 텍스처 설정
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/처음화면.png")) {
        return -1;  // 배경 이미지 파일을 찾지 못하면 프로그램 종료
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // 배경 이미지를 스프라이트로 변환

    // 폰트 로드 및 설정
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;  // 폰트 파일을 찾지 못하면 프로그램 종료
    }

    // 시작 버튼 생성: 크기, 색상, 위치 설정
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setFillColor(sf::Color(92, 112, 94));  // 녹색 계열
    startButton.setPosition(500, 570);                // (x, y) 위치

    // 시작 버튼 텍스트 생성 및 설정
    sf::Text startButtonText(L"게임 시작", font, 30);
    startButtonText.setFillColor(sf::Color::White);  // 하얀색 텍스트
    startButtonText.setPosition(545, 577);          // 텍스트 위치 조정

    // 게임 설명 버튼 생성: 크기, 색상, 위치 설정
    sf::RectangleShape instructionsButton(sf::Vector2f(200, 50));
    instructionsButton.setFillColor(sf::Color(92, 112, 94));  // 녹색 계열
    instructionsButton.setPosition(500, 634);                // (x, y) 위치

    // 게임 설명 버튼 텍스트 생성 및 설정
    sf::Text instructionsButtonText(L"게임 방법", font, 30);
    instructionsButtonText.setFillColor(sf::Color::White);  // 하얀색 텍스트
    instructionsButtonText.setPosition(545, 641);          // 텍스트 위치 조정

    // 창이 열려 있는 동안 실행되는 메인 루프
    while (window.isOpen()) {
        sf::Event event;  // 이벤트 객체 생성
        while (window.pollEvent(event)) {  // 이벤트 처리
            if (event.type == sf::Event::Closed)  // 창 닫기 이벤트
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {  // 마우스 클릭 이벤트
                if (event.mouseButton.button == sf::Mouse::Left) {  // 왼쪽 버튼 클릭
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // 마우스 좌표 가져오기

                    // 시작 버튼 클릭 처리
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  // 현재 창 닫기
                        startGame();     // 외부 함수 호출 (게임 시작)
                    }

                    // 게임 설명 버튼 클릭 처리
                    if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();        // 현재 창 닫기
                        showDescription();     // 외부 함수 호출 (게임 설명 표시)
                    }
                }
            }
        }

        // 화면 그리기
        window.clear();                       // 이전 화면 지우기
        window.draw(backgroundSprite);        // 배경 이미지 그리기
        window.draw(startButton);             // 시작 버튼 그리기
        window.draw(startButtonText);         // 시작 버튼 텍스트 그리기
        window.draw(instructionsButton);      // 게임 설명 버튼 그리기
        window.draw(instructionsButtonText);  // 게임 설명 버튼 텍스트 그리기
        window.display();                     // 새로 그린 화면을 디스플레이
    }

    return 0;  // 프로그램 정상 종료
}
