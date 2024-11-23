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

        // 화면을 새로 그리기 전에 배경 이미지 그리기
        window.clear();  // 배경을 지운 후

        // 배경 이미지를 화면에 그리기
        window.draw(backgroundSprite);

        // 화면에 그린 모든 것을 출력
        window.display();
        
        return 0;  // 프로그램 종료
    }

    
