#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
RenderWindow game(VideoMode(2000, 2000), "Race Dan");
game.setFramerateLimit(60);

Texture car;
Texture background;

car.loadFromFile("f12.png");
background.loadFromFile("super.png");

Sprite spriteBack(background);
Sprite spriteCar(car);

spriteCar.setPosition(400, 400);
spriteCar.setOrigin(22, 22);

float x = 300;
float y = 300;

float speed = 0;
float angle = 0;

float maxSpeed = 10;
float accelerate = 0.2;
float decelerate = 0.2;
float corner = 0.08;

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

    if (Keyboard::isKeyPressed(Keyboard::Up)) up = 1;
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


    game.clear(Color::Black);
    game.draw(spriteBack);


    spriteCar.setPosition(x, y);
    spriteCar.setRotation(angle * 180 / 3.142);
    spriteCar.setColor(Color::Red);
    game.draw(spriteCar);
    game.display();
}
   
    return 0;
}