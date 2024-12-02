#include <SFML/Graphics.hpp>                   
#include <random>     
#include <string>
#include <deque>				//컨테이너를 사용해 뱀의 몸통 관리

const float Snake_Speed = 25.f;			// 기본 뱀 이동 속도
const sf::Vector2f GRID_SIZE(25.f, 25.f); // 그리드 크기 (뱀 및 먹이 정렬을 위한 기준) 25 * 25 픽셀 크기
/*그리드란, 게임 화면을 작은 사각형들로 나누어 각 객체(뱀, 먹이 등)가
정확히 해당 사각형의 경계선에 맞춰 배치되도록 정렬하는 방식을 의미 */
const int width = 906;					// 게임 화면의 너비 
const int height = 795;					// 게임 화면의 높이

//뱀의 방향을 나타내는 열겨형
enum Movement { STOP = 0, UP, DOWN, LEFT, RIGHT };

//먹이 구조체
struct Prey {
    sf::Sprite sprite;			//먹이를 나타내는 스프라이트
    std::string type;			//먹이 타입 (사과, 병아리, 쥐)
};

//먹이 랜덤 위치 생성
sf::Vector2f RandomPosition() {
    std::random_device rd;           // 하드웨어 난수 생성기 초기화
    std::mt19937 gen(rd());          // Mersenne Twister 엔진 사용
    std::uniform_int_distribution<int> xDist(0, (width / (int)GRID_SIZE.x) - 1);
    // x좌표: 그리드 크기를 기준으로 랜덤 정수 값 생성
    std::uniform_int_distribution<int> yDist(0, (height / (int)GRID_SIZE.y) - 1);
    // y좌표: 그리드 크기를 기준으로 랜덤 정수 값 생성
    return sf::Vector2f(xDist(gen) * GRID_SIZE.x, yDist(gen) * GRID_SIZE.y);
    // 랜덤한 x, y 위치를 반환 (그리드 정렬 적용)
}

void startGame() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");
    // RenderWindow 생성: 주어진 크기와 제목으로 게임 창 생성
    window.setFramerateLimit(60);
    // 프레임 속도 제한: 게임이 초당 60 프레임으로 동작하도록 설정

    // 폰트 로드 및 설정
    sf::Font font;  // 폰트 객체 생성
    if (!font.loadFromFile("C:/Users/lmslh/source/repos/c++/font_/yangjinche.otf")) {  // 폰트 파일 로드
        return;  // 폰트 로드 실패 시 함수 종료
    }


    sf::Texture backgroundTexture, snakeHeadTexture, snakeBodyTexture, appleTexture, chickTexture, mouseTexture;
    backgroundTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/게임창.png");   // 배경 텍스처 로드
    snakeHeadTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/뱀 머리.png");  // 뱀 머리 텍스처 로드
    snakeBodyTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/뱀꼬리.png");  // 뱀 몸통 텍스처 로드
    appleTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/사과.png");         // 사과 텍스처 로드
    chickTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/병아리.png");       // 병아리 텍스처 로드
    mouseTexture.loadFromFile("C:/Users/lmslh/source/repos/c++/images/쥐.png");             // 쥐 텍스처 로드

    sf::Sprite background(backgroundTexture);				// 배경 스프라이트 생성
    sf::Sprite snakeHead(snakeHeadTexture);					// 뱀 머리 스프라이트 생성
    snakeHead.setPosition(width / 2.f, height / 2.f);		// 뱀 머리 위치 - 중앙

    std::deque<sf::Sprite> snakeBody;  // 뱀의 몸통을 관리할 deque 컨테이너
    Movement direction = STOP;       // 뱀의 초기 이동 방향
    Movement nextDirection = direction; // 사용자가 설정한 다음 방향

    float speed = Snake_Speed;	  // 현재 뱀의 이동 속도 (기본 속도로 시작)
    float timer = 0.f;			  // 이동 타이머 초기화
    sf::Clock clock;			  // SFML Clock 객체로 시간 측정
    bool gameover = false;		  // 게임 종료 플래그 초기화
    int score = 0;				  // 게임 점수 초기화

    Prey prey;									// prey 구조체 생성
    prey.sprite.setTexture(appleTexture);		// 초기 먹이 타입은 "apple"
    prey.type = "apple";
    prey.sprite.setPosition(RandomPosition());  // 랜덤한 위치에 배치

    while (window.isOpen()) {
        // window.isOpen(): 게임 창이 열려 있는지 확인
        sf::Event event;
        // SFML 이벤트 객체: 키보드, 마우스 및 창 이벤트 처리
        while (window.pollEvent(event)) {
            // 이벤트 감지 루프: 이벤트 큐에서 이벤트를 하나씩 가져옴. 큐에 이벤트가 있을 때 처리
            if (event.type == sf::Event::Closed)
                // 창 닫기 이벤트가 발생하면
                window.close();  // 창 닫음

            // 방향 입력 
            if (event.type == sf::Event::KeyPressed) {
                // 키가 눌렸을 때 이벤트
                if (event.key.code == sf::Keyboard::W && direction != DOWN) nextDirection = UP;
                if (event.key.code == sf::Keyboard::S && direction != UP) nextDirection = DOWN;
                if (event.key.code == sf::Keyboard::A && direction != RIGHT) nextDirection = LEFT;
                if (event.key.code == sf::Keyboard::D && direction != LEFT) nextDirection = RIGHT;
                // W, A, S, D 키 입력으로 방향 전환
                // 반대 방향으로의 전환 방지 (ex: UP -> DOWN 불가)
            }
        }

        direction = nextDirection;  // 실제로 이동할 방향 설정

        // 뱀의 머리 위치 업데이트
        sf::Vector2f nextPosition = snakeHead.getPosition();
        if (direction == UP) nextPosition.y -= GRID_SIZE.y;   // 위로 이동
        if (direction == DOWN) nextPosition.y += GRID_SIZE.y; // 아래로 이동
        if (direction == LEFT) nextPosition.x -= GRID_SIZE.x; // 왼쪽으로 이동
        if (direction == RIGHT) nextPosition.x += GRID_SIZE.x; // 오른쪽으로 이동

        // 뱀 머리 위치 업데이트
        snakeHead.setPosition(nextPosition);  // 계산된 새로운 위치로 뱀 머리 이동

        // 먹이와의 충돌 체크
        if (snakeHead.getGlobalBounds().intersects(prey.sprite.getGlobalBounds())) {
            // 뱀 머리와 먹이의 충돌을 검사
            if (prey.type == "apple") {  // 사과 먹이를 먹으면
                score += 1;  // 점수 증가
                sf::Sprite newSegment(snakeBodyTexture);  // 새로운 몸통 생성
                if (!snakeBody.empty()) newSegment.setPosition(snakeBody.back().getPosition());  // 몸통 뒤에 위치
                else newSegment.setPosition(snakeHead.getPosition());  // 처음엔 머리 위치에 몸통 추가
                snakeBody.push_back(newSegment);  // 뱀 몸통에 새로 생성된 몸통 추가
            }
            else if (prey.type == "chick") {  // 병아리 먹이를 먹으면
                score += 1;  // 점수 증가
            }
            else if (prey.type == "mouse") {  // 쥐 먹이를 먹으면
                score += 2;  // 점수 2점 증가
                sf::Sprite newSegment(snakeBodyTexture);  // 새로운 몸통 생성
                if (!snakeBody.empty()) newSegment.setPosition(snakeBody.back().getPosition());  // 몸통 뒤에 위치
                else newSegment.setPosition(snakeHead.getPosition());  // 처음엔 머리 위치에 몸통 추가
                snakeBody.push_back(newSegment);  // 뱀 몸통에 새로 생성된 몸통 추가
            }
        }

        // 새로운 먹이 랜덤 위치에 설정
        prey.sprite.setPosition(RandomPosition());  // 새 위치로 먹이 배치
        int preyType = rand() % 3;  // 랜덤으로 먹이 종류 결정

        if (preyType == 0) {
            prey.sprite.setTexture(appleTexture);  // 사과
            prey.type = "apple";
        }
        else if (preyType == 1) {
            prey.sprite.setTexture(chickTexture);  // 병아리
            prey.type = "chick";
        }
        else {
            prey.sprite.setTexture(mouseTexture);  // 쥐
            prey.type = "mouse";
        }
        // 게임 화면 그리기
        window.clear();  // 화면 초기화
        window.draw(background);  // 배경 그리기
        for (const auto& segment : snakeBody) window.draw(segment);  // 뱀 몸통 그리기
        window.draw(snakeHead);  // 뱀 머리 그리기
        window.draw(prey.sprite);  // 먹이 그리기
        window.display();  // 화면에 모든 객체 출력
    }
}