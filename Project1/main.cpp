#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>

using namespace sf;

int main()
{
    RenderWindow game(VideoMode(1920, 1080), "Retro Drive!");
    game.setFramerateLimit(60);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("critical.wav")) {
        return -1;
    }
    sf::Sound sound;

    sound.setBuffer(buffer);

    struct Player {
        int tileX;
        int tileY;
    };

    int points = 200;


    Texture car;
    Texture background;
    Texture gem;
    Texture nogo;
    Texture nogoTwo;

    nogo.loadFromFile("no.png");
    nogoTwo.loadFromFile("go.png");
    car.loadFromFile("anotherf1.png");
    background.loadFromFile("finaltrack.png");
    gem.loadFromFile("f1.png");

    Sprite noGoZone(nogo);
    Sprite noGoZoneTwo(nogoTwo);
    Sprite spriteBack(background);
    Sprite spriteCar(car);
    Sprite spriteGem(gem);

    // 960, 800

    noGoZone.setPosition(750, 350);
    noGoZone.setOrigin(800 / 2, 100 / 2);
    noGoZoneTwo.setPosition(750, 250);

    spriteCar.setPosition(100, 100);

    spriteCar.setOrigin(32 / 2, 32 / 2);

    float x = 300;
    float y = 300;

    float speed = 0;
    float angle = 0;

    int maxSpeed = 15;
    float accelerate = 0.2;
    float decelerate = 0.2;
    float corner = 0.08;

    sf::Vector2f checkOne = { 400, 200 };
    sf::Vector2f checkTwo = { 1200, 200 };
    sf::Vector2f checkThree = { 400, 1000 };
    sf::Vector2f checkFour = { 1200, 1000 };

    float randomX = rand() % 1000 + 1;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    while (game.isOpen()) {
        Event e;
        while (game.pollEvent(e)) {
            if (e.type == Event::Closed)
                game.close();
        }

        bool up = 0;
        bool down = 0;
        bool right = 0;
        bool left = 0;

        if (Keyboard::isKeyPressed(Keyboard::Up)) up = 1, points -= 0.1;
        if (Keyboard::isKeyPressed(Keyboard::Down)) down = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) right = 1;
        if (Keyboard::isKeyPressed(Keyboard::Left)) left = 1;


        if (up && speed < maxSpeed)

            if (speed < 0) speed = speed + decelerate;

            else speed = speed + accelerate;

        if (down && speed > -maxSpeed)
            if (speed > 0) speed = speed - decelerate;
            else speed = speed - accelerate;

        if (!up && !down)
            if (speed - decelerate > 0) speed = speed - decelerate;
            else if (speed + decelerate < 0) speed = speed + decelerate;
            else speed = 0;

        if (right && speed != 0) angle = angle + corner * (speed / maxSpeed);
        if (left && speed != 0) angle = angle - corner * (speed / maxSpeed);

        x = x + sin(angle) * speed;
        y = y - cos(angle) * speed;



        
        

        std::string Speed_str = std::to_string(floor(speed * 10));
       
        sf::Text text("Speed: " + Speed_str, font, 50);




        game.clear(Color::Black);
        game.draw(spriteBack);
        text.setFillColor(Color::Red);


        // set track
        // count laps
        // horn sound
        // if points = 0 GAME OVER


        spriteCar.setPosition(x, y);
        spriteCar.setRotation(angle * 180 / 3.14159);


        sf::FloatRect boundingBox = spriteCar.getGlobalBounds();
        sf::FloatRect colBox = noGoZone.getGlobalBounds();
        // sf::Vector2f pos = { randomX, randomY };

        if (colBox.contains(x, y)) {
            x = 100;
            y = 100;
            speed = 0;
            spriteCar.setRotation(180);
        }

        sf::FloatRect lowZone = noGoZoneTwo.getGlobalBounds();

        if (lowZone.contains(x, y)) {
            x = 100;
            y = 100;
            speed = 0;
            spriteCar.setRotation(180);
        }

      

        if (x  < 0 || x  > 1920 || y < 0 || y > 1080) {
                x = 100;
                y = 100;
                speed = 0;
                spriteCar.setRotation(180);
        }


if (boundingBox.contains(checkOne))
{
    points = points + 2;
    
    sound.play();
}

if (boundingBox.contains(checkTwo))
{
    points = points + 2;
    sound.play();
}

if (boundingBox.contains(checkThree))
{
    points = points + 2;
    sound.play();
}

if (boundingBox.contains(checkFour))
{
    points = points + 2;
    sound.play();
}

if (points > 500) {
    points = 500;
}

    std::string Points_str = std::to_string(points);
    sf::Text pointsText("Fuel: " + Points_str, font, 50);

    pointsText.setPosition(0, 100);
    spriteCar.setColor(Color::Red);

    std::string Rand_str = std::to_string(randomX);
    sf::Text randText("Check Point: " + Rand_str, font, 50);
    
    randText.setPosition(0, 200);

    spriteGem.setPosition(checkOne);
  
    game.draw(spriteCar);
    game.draw(text);
    game.draw(pointsText);
    game.draw(randText);
    game.draw(spriteGem);
    spriteGem.setPosition(checkTwo);
    game.draw(spriteGem);
    spriteGem.setPosition(checkThree);
    game.draw(spriteGem);
    spriteGem.setPosition(checkFour);
    game.draw(noGoZone);
    game.draw(noGoZoneTwo);

    game.draw(spriteGem);
    game.display();
}
   
    return 0;
}