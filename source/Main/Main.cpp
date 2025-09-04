#include "Game.h"


int main() {
    /*// Инициализация окна
    RenderWindow window(VideoMode(1024, 768), "Hello SFML");
    // фрейм-лимит
    window.setFramerateLimit(60);

    //текстура коробки
    Texture Box_Texture;
    if (!Box_Texture.loadFromFile("vecteezy_wooden-box-clipart-design-illustration_9342647.png")) return EXIT_FAILURE;

    //текстура для круга
    Texture circle_Texture;
    if (!circle_Texture.loadFromFile("vecteezy_soldier-png-graphic-clipart-design_19807017.png")) return EXIT_FAILURE;

    //текстура для земли
    Texture ground_Texture;
    if (!ground_Texture.loadFromFile("трава на прямоугольник.png")) return EXIT_FAILURE;
    ground_Texture.setRepeated(true);

    //Текстура спрайта земли
    Texture Sprite_G_Texture;
    if (!Sprite_G_Texture.loadFromFile("трава спрайтом.png")) return EXIT_FAILURE;
    Sprite_G_Texture.setRepeated(true);

    //Текстура спрайта бэкграунда
    Texture BackGround_Texture;
    if (!BackGround_Texture.loadFromFile("бэк.png")) return EXIT_FAILURE;


    //Шрифт для текста
    Font font;
    if (!font.loadFromFile("PixelifySans-VariableFont_wght.ttf")) return EXIT_FAILURE;
    
    //Таймер
    Text AfterDeath_Timer;
    AfterDeath_Timer.setFont(font);
    AfterDeath_Timer.setCharacterSize(50);
    AfterDeath_Timer.setFillColor(Color::Black);
    AfterDeath_Timer.setPosition(300, 620);


    //Текст со счетчиком попыток
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Red);
    text.setPosition(700, 100);

    //Спрайт Game Over
    Texture GO_Texture;
    if (!GO_Texture.loadFromFile("гамовер.png")) return EXIT_FAILURE;
    Sprite GoSprite(GO_Texture);
    GoSprite.setPosition(310, 200);
    Vector2u textureSize = GO_Texture.getSize();
    float desiredWidth = 400.f;
    float desiredHeight = 400.f;
    GoSprite.setScale(desiredWidth / textureSize.x, desiredHeight / textureSize.y);

    //Инициализация текстуры фона
    Sprite backSprite(BackGround_Texture);

    //Инициализация спрайта земли
    Sprite grassSprite(Sprite_G_Texture);
    grassSprite.setTextureRect(IntRect(0, 0, 1024, 100));
    grassSprite.setPosition(0, 640);
    
    //Инициализация круга
    CircleShape circle(30.f);
    circle.setPosition(500, 645);
    circle.setTexture(&circle_Texture);

    //Инициализация коробок
    RectangleShape rectangle;
    rectangle.setSize(Vector2f(40, 40));
    rectangle.setPosition(700, 660);
    rectangle.setTexture(&Box_Texture);
    
    //Инициализация земли
    RectangleShape ground;
    ground.setSize(Vector2f(1024, 100));
    ground.setPosition(0, 700);
    ground.setTexture(&ground_Texture);
    ground.setTextureRect(IntRect(0, 0, 1024, 100));

    //Массив положений коробок
    vector<Vector2f> positions = {
        {700, 660},
        {200, 660},
    };

    //переменные
    int Try = 0;
    bool isAlive = true;
    float speed = 200.f;
    bool circleVisible = true;
    float velocityY = 0.f;
    bool isJumping = false;
    float jumpStrenght = -400.0f;
    float timeLimit = 10.0f; 
    float deltaTime = 0.016f;
    const float gravity = 980.0f;
    Clock RespawnClock;

    //цикл окна
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        //переменные для обработки movement
        velocityY += gravity * deltaTime;
        Vector2 movement(0.f, velocityY * deltaTime);
        
        //Обработка управления и движения
        if (isAlive) {
            if (Keyboard::isKeyPressed(Keyboard::Space) && !isJumping) {
                velocityY = jumpStrenght;
                isJumping = true;
                cout << "jump";
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) movement.x -= speed * deltaTime;
            if (Keyboard::isKeyPressed(Keyboard::D)) movement.x += speed * deltaTime;

            circle.move(movement);
        }
        //логика столкновения с землей
        FloatRect circleBounds = circle.getGlobalBounds();
        FloatRect groundBounds = ground.getGlobalBounds();

        if (circleBounds.intersects(groundBounds)) {
            float circleBottom = circleBounds.top + circleBounds.height;
            float groundTop = groundBounds.top;
            if (velocityY >= 0 && abs(circleBottom - groundTop) < 20.f)
            {
                circle.setPosition(circle.getPosition().x, groundTop - circleBounds.height + 5 );
                velocityY = 0.f;
                isJumping = false;
            }
        }

        //логика столкновения с ящиками
        for (const auto& pos : positions) {
            rectangle.setPosition(pos);

            FloatRect rectBounds = rectangle.getGlobalBounds();

            float padding = -10.f;
            FloatRect shrunkBounds(
                rectBounds.left - padding,
                rectBounds.top - padding,
                rectBounds.width + 2 * padding,
                rectBounds.height + 2 * padding
            );

            if (circle.getGlobalBounds().intersects(shrunkBounds))
            {
                if (isAlive) {
                    circleVisible = false;
                    isAlive = false;
                    RespawnClock.restart();
                }
                break;
            }
        }

        //отрисовка
        window.clear(Color::Black);
        window.draw(backSprite);
        window.draw(ground);
        window.draw(grassSprite);
        text.setString(String(L"Попыток: ") + to_string(Try));
        window.draw(text);
        for (const auto& pos : positions) {
            rectangle.setPosition(pos);
            window.draw(rectangle);
        }
        if (circleVisible == true) window.draw(circle);

        //Функция Game over
        if (!isAlive) {
            window.draw(GoSprite);  
            float elapsed = RespawnClock.getElapsedTime().asSeconds();
            float remaining = max(0.0f, timeLimit - elapsed);
            AfterDeath_Timer.setString(String(L"Возрождение: ") + to_wstring(static_cast<int>(remaining * 10) / 10.0));
            window.draw(AfterDeath_Timer);
            if (Keyboard::isKeyPressed(Keyboard::R)) {
                Try++;
                isAlive = true;
                circle.setPosition(Vector2f(500, 645));
                circleVisible = true;
                velocityY = 0.f;
                isJumping = false;
            }
            if (remaining <= 0.f) {
                Try++;
                isAlive = true;
                circle.setPosition(Vector2f(500, 645));
                circleVisible = true;
                velocityY = 0.f;
                isJumping = false;
            }
        }
        window.display();
    }*/
    Game game;
    game.gameLoad();

    return 0;
}