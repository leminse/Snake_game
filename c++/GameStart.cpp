#include <SFML/Graphics.hpp>   // SFML의 그래픽 기능을 사용하기 위한 헤더 파일
#include <SFML/Window.hpp>     // SFML의 윈도우 기능을 사용하기 위한 헤더 파일
#include <vector>               // 벡터를 사용하기 위한 헤더 파일
#include <random>               // 난수 생성을 위한 헤더 파일

void startGame() {

    // 게임 창 크기와 제목 설정
    const int tileSize = 20;    // 각 타일의 크기 (20x20 픽셀)
    const int width = 45;       // 게임 화면의 너비 (타일의 수)
    const int height = 40;      // 게임 화면의 높이 (타일의 수)
    sf::RenderWindow window(sf::VideoMode(width * tileSize, height * tileSize), "Snake Game");  // 게임 창 생성
    //VideoMode는 45 * 20, 40 * 20 사이즈.

    // 배경 이미지 로드 및 텍스처 설정
    sf::Texture backgroundTexture;   // 배경을 위한 텍스처 객체
    if (!backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임창.png")) {  // 배경 이미지 파일 로드
        return;  // 이미지 로드 실패 시 함수 종료
    }
    sf::Sprite backgroundSprite(backgroundTexture);   // 배경 이미지를 표시할 스프라이트 객체 생성

    // 폰트 로드 및 설정
    sf::Font font;  // 폰트 객체 생성
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {  // 폰트 파일 로드
        return;  // 폰트 로드 실패 시 함수 종료
    }

    //게임 객체 초기화
    bool gameover = false;              //게임 오버
    int x = width / 2, y = height / 2;   // 뱀의 초기 위치 - 중앙
    int preyX, preyY;                       //먹이 위치
    int score = 0;                          //점수
    std::vector<sf::Vector2f> tail;            //뱀의 움직임을 부드럽게 하기 위해 Vector2f를 사용. (실수)
    // 뱀의 꼬리 (이전 위치 기록용 벡터)
    enum Movement { STOP = 0, LEFT, RIGHT, UP, DOWN };          //멈춤, 왼쪽, 오른쪽, 위, 아래
    Movement beginning = STOP;                      //뱀의 처음 방향 = 멈춤

    std::random_device ra;                          //랜덤 먹이 위치
    std::mt19937 ge(ra());                          // Mersenne Twister 알고리즘을 사용한 난수 생성기
    std::uniform_int_distribution<> dis(0, width - 1);
    preyX = dis(ge);                                    //랜덤한 위치에 먹이 생성
    preyY = dis(ge);                                    //랜덤한 위치에 먹이 생성

    // 게임 화면 그리기용 타일 설정
    sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
    // RectangleShape: 직사각형 모양을 그리기 위한 클래스

    sf::Texture appleTexture;
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/사과.png");

    sf::Texture chickTexture;
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/병아리.png");

    sf::Texture mouseTexture;
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/쥐.png");

    sf::Texture snakeHeadTexture;
    snakeHeadTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/뱀 머리.png");

    sf::Texture snakeTailTexture;
    snakeTailTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/뱀 꼬리.png");

    sf::Sprite preySprite;   // 먹이를 그릴 스프라이트 객체

    sf::Sprite snakeHeadSprite(snakeHeadTexture);   // 뱀 머리

    sf::Sprite snakeTailSprite(snakeTailTexture);   // 뱀 꼬리

    // 속도를 조절하기 위한 sf::Clock 사용
    sf::Clock clock;
    // sf::Clock는 시간 측정을 위한 클래스. 
    float MoveSpeed = 0.3f;
    // 뱀의 이동 속도를 초 단위로 설정. 낮을수록 더 빠르게 움직임.
    float lastMoveTime = 0.f;
    // 마지막으로 뱀이 움직인 시간을 저장.
    bool speedUp = false;  // 속도 증가 여부
    bool slowDown = false;  // 속도 감소 여부
    float speedChangeTime = 0.f;  // 속도 변화 시간
    int lengthChange = 0;  // 길이 변화 값 (먹이 종류에 따라 다름)

    // 게임 루프 시작
    while (window.isOpen()) {
        // window.isOpen(): 게임 창이 열려 있는지 확인합니다.
        sf::Event event;
        while (window.pollEvent(event)) {
            // 이벤트 큐에서 이벤트를 하나씩 가져옵니다.
            if (event.type == sf::Event::Closed) {
                // 창 닫기 이벤트가 발생하면
                window.close();  // 창을 닫습니다.
            }
        }

        if (!gameover) {
            // 게임 오버 상태가 아니라면 실행
            float deltaTime = clock.restart().asSeconds();
            // clock.restart(): 시계를 재설정하고, 이전 시점부터의 경과 시간을 초 단위로 반환.
            if (deltaTime + lastMoveTime >= MoveSpeed) {
                // deltaTime(경과 시간)과 lastMoveTime(마지막 이동 시간의 합)이 moveSpeed보다 크면
                lastMoveTime = deltaTime;
                // lastMoveTime을 deltaTime으로 업데이트하여 다음 이동 시점을 설정

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && beginning != RIGHT) beginning = LEFT;   // 왼쪽 방향키
                // 왼쪽 화살표 키가 눌리면 dir를 LEFT로 설정
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && beginning != LEFT) beginning = RIGHT;   // 오른쪽 방향키
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && beginning != DOWN) beginning = UP;   // 위 방향키
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && beginning != UP) beginning = DOWN;   // 아래 방향키

                sf::Vector2f prev(x, y);   // 뱀 머리의 이전 위치 저장
                sf::Vector2f prev2;  // 꼬리의 이전 위치 저장용 임시 변수
                for (size_t i = 0; i < tail.size(); i++) {   // 꼬리 부분 이동
                    //size_t : 컨테이너의 크기나 배열의 크기 등 비음수값을 다룰 때 최적의 선택.
                    // 꼬리의 각 부분을 업데이트
                    prev2 = tail[i];
                    tail[i] = prev;
                    prev = prev2;
                }

                // 이동 방향에 따라 뱀 머리 위치 업데이트
                switch (beginning) {
                case LEFT: x--; break;
                case RIGHT: x++; break;
                case UP: y--; break;
                case DOWN: y++; break;
                default: break;
                }

                // 벽에 닿으면 게임 오버
                if (x < 0 || x >= width || y < 0 || y >= height) {
                    // x가 0보다 작거나 width 이상, 또는 y가 0보다 작거나 height 이상이면
                    gameover = true;  // 게임 오버 상태로 설정
                }

                // 뱀이 자기 꼬리에 닿으면 게임 오버
                for (auto& segment : tail) {
                    if (segment.x == x && segment.y == y) {
                        // 뱀의 현재 머리 위치가 꼬리의 어느 부분과 동일하면
                        gameover = true;  // 게임 오버 상태로 설정
                    }
                }
                window.clear();  // 화면을 지운다

                window.draw(backgroundSprite);  // 배경을 그린다

                snakeHeadSprite.setPosition(x * tileSize, y * tileSize);  // 뱀 머리 위치 설정
                window.draw(snakeHeadSprite);  // 뱀 머리 그리기

                sf::Text scoreText;
                scoreText.setFont(font);  // 점수 텍스트에 폰트 설정
                scoreText.setString("Score: " + std::to_string(score));  // 점수 텍스트 설정
                scoreText.setCharacterSize(24);  // 텍스트 크기 설정
                scoreText.setFillColor(sf::Color::White);  // 텍스트 색상 설정
                scoreText.setPosition(10, 10);  // 텍스트 위치 설정
                window.draw(scoreText);  // 점수 텍스트 그리기

                window.display();  // 화면을 갱신한다
            }
        }
    }