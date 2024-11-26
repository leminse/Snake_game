#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <random>

void main();


// 게임 시작 로직을 포함하는 함수
void startGame() {
    // 게임 창 크기와 제목 설정
    sf::RenderWindow window(sf::VideoMode(906, 795), "Snake Game");

    // 배경 이미지 로드 및 텍스처 설정
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임창.png")) {
        return;  // 배경 이미지 파일을 찾지 못하면 프로그램 종료
    }
    sf::Sprite backgroundSprite(backgroundTexture);  // 배경 이미지를 스프라이트로 변환

    // 폰트 로드 및 설정
    sf::Font font;
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {
        return;  // 폰트 파일을 찾지 못하면 프로그램 종료
    }

    // 게임 상태 변수 초기화
    const int width = 20;
    const int height = 15;
    const int tileSize = 30;
    bool gameOver = false;
    int x = width / 2, y = height / 2, fruitX, fruitY, score = 0;
    std::vector<sf::Vector2i> tail;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir = STOP;

    // 먹이의 초기 위치 설정
    fruitX = rand() % width;
    fruitY = rand() % height;

    // 게임 화면 그리기
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize)); // 각 타일 크기 설정
    sf::Texture appleTexture;
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/사과.png");
    sf::Texture chickTexture;
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/병아리.png");
    sf::Texture mouseTexture;
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/쥐.png");
    sf::Sprite fruitSprite;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 게임 로직 및 입력 처리
        if (!gameOver) {
            // 사용자 입력 (방향키로 뱀 이동)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir = LEFT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir = RIGHT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir = UP;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir = DOWN;

            // 뱀 이동 및 게임 로직
            sf::Vector2i prev(x, y);
            sf::Vector2i prev2;
            for (size_t i = 0; i < tail.size(); i++) {
                prev2 = tail[i];
                tail[i] = prev;
                prev = prev2;
            }

            switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
            }

            // 벽 충돌 검사
            if (x < 0 || x >= width || y < 0 || y >= height) {
                gameOver = true;
            }

            // 자기 자신과 충돌 검사
            for (auto& segment : tail) {
                if (segment.x == x && segment.y == y) {
                    gameOver = true;
                }
            }

            // 먹이 먹기 처리
            if (x == fruitX && y == fruitY) {
                score += 1;
                tail.push_back(sf::Vector2i(x, y));
                fruitX = rand() % width;
                fruitY = rand() % height;
            }

            // 게임 화면 그리기
            window.clear();

            // 배경 그리기
            window.draw(backgroundSprite);  // 배경을 먼저 그리기

            // 맵 그리기
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    tile.setPosition(i * tileSize, j * tileSize);
                    tile.setFillColor(sf::Color(50, 50, 50));
                    window.draw(tile);
                }
            }

            // 뱀 머리 그리기
            tile.setPosition(x * tileSize, y * tileSize);
            tile.setFillColor(sf::Color::Green);
            window.draw(tile);

            // 뱀 꼬리 그리기
            for (auto& segment : tail) {
                tile.setPosition(segment.x * tileSize, segment.y * tileSize);
                tile.setFillColor(sf::Color(0, 128, 0));
                window.draw(tile);
            }

            // 먹이 그리기
            fruitSprite.setTexture(appleTexture);
            fruitSprite.setPosition(fruitX * tileSize, fruitY * tileSize);
            window.draw(fruitSprite);

            // 점수 표시
            sf::Text scoreText("점수: " + std::to_string(score), font, 20);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(10, 10);
            window.draw(scoreText);

            window.display();
        }
        else {
            window.clear();
            sf::Text gameOverText("Game Over! Final Score: " + std::to_string(score), font, 30);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(width * tileSize / 4, height * tileSize / 2);

            // 시작 버튼 생성: 크기, 색상, 위치 설정
            sf::RectangleShape firstButton(sf::Vector2f(200, 50));
            firstButton.setFillColor(sf::Color(92, 112, 94));  // 녹색 계열
            firstButton.setPosition(500, 570);                // (x, y) 위치
            // 시작 버튼 텍스트 생성 및 설정
            sf::Text firstButtonText(L"처음으로", font, 30);
            firstButtonText.setFillColor(sf::Color::White);  // 하얀색 텍스트
            firstButtonText.setPosition(545, 577);          // 텍스트 위치 조정

            if (event.type == sf::Event::MouseButtonPressed) {  // 마우스 클릭 이벤트
                if (event.mouseButton.button == sf::Mouse::Left) {  // 왼쪽 버튼 클릭
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);  // 마우스 좌표 가져오기

                    // 시작 버튼 클릭 처리
                    if (firstButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        window.close();  // 현재 창 닫기
                        main();     // 외부 함수 호출 
                    }
                }
            }
            window.draw(gameOverText);
            window.draw(firstButton);
            window.draw(firstButtonText);
            window.display();
        }
    }

}
