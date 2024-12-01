#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


void startGame();         // 게임 시작 함수
void showDescription();   // 게임 설명 함수

int main() {
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/처음 화면.png")) {
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);             // 배경을 그릴 스프라이트 객체

    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return -1;
    }
                    
    // 시작 버튼 생성
    sf::RectangleShape startButton(sf::Vector2f(250, 60));          //버튼 크기
    startButton.setFillColor(sf::Color(92, 112, 94));               //색상
    startButton.setPosition(340, 470);                              //위치

    // 시작 버튼 텍스트
    sf::Text startButtonText(L"게임 시작", font, 40);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(390, 475);

    // 게임 설명 버튼 생성
    sf::RectangleShape instructionsButton(sf::Vector2f(250, 60));
    instructionsButton.setFillColor(sf::Color(92, 112, 94));
    instructionsButton.setPosition(340, 554);

    // 게임 설명 버튼 텍스트
    sf::Text instructionsButtonText(L"게임 방법", font, 40);
    instructionsButtonText.setFillColor(sf::Color::White);
    instructionsButtonText.setPosition(390, 561);

    // 메인 루프: 창이 열려있는 동안 반복 실행
    while (window.isOpen()) {
        sf::Event event;                                        // 이벤트 객체 생성
        while (window.pollEvent(event)) {                       // 발생한 이벤트를 큐에서 가져와 처리
            if (event.type == sf::Event::Closed)
                window.close();                                 // 창 닫기 이벤트 발생 시 창을 닫음

            // 마우스 클릭 이벤트 처리
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // 마우스 왼쪽 버튼 클릭
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window); // 클릭한 마우스 위치 가져오기

                    // 시작 버튼 클릭 여부 확인
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close(); // 창 닫기
                        startGame();    // 게임 시작 함수 호출
                    }

                    // 게임 설명 버튼 클릭 여부 확인
                    if (instructionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close(); // 창 닫기
                        showDescription(); // 게임 설명 함수 호출
                    }
                }
            }
        }

        // 화면 그리기
        window.clear();                   // 창을 깨끗이 지움
        window.draw(backgroundSprite);    // 배경 이미지 그리기
        window.draw(startButton);         // 시작 버튼 그리기
        window.draw(startButtonText);     // 시작 버튼 텍스트 그리기
        window.draw(instructionsButton);  // 설명 버튼 그리기
        window.draw(instructionsButtonText); // 설명 버튼 텍스트 그리기
        window.display();                 // 화면 업데이트
    }

    return 0; // 프로그램 종료
}
