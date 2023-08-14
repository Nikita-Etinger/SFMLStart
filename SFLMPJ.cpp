#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define random(a,b) a + rand()%(b-a-1)
const int sizeX = 200;
const int sizeY = 200;

int main()
{
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "SFML works!");
    std::vector<sf::CircleShape> circle;
    int countX = 10;
    float shapeSize = window.getSize().x / (countX * 2);
    int countY = window.getSize().y / (countX * 2);
    srand(time(NULL));
    if (countX > shapeSize) countX -= 1;
    for (int j = 0; j < countY; j++) {
        for (int i = 0; i < countX; i++) {
            sf::CircleShape shape(shapeSize);
            shape.setPosition(shapeSize * 2 * i, shapeSize * 2 * j);
            shape.setFillColor(sf::Color(random(0, 255), random(0, 255), random(0, 255), random(0, 255)));
            circle.push_back(shape);
        }
    }

    std::cout << circle.size() << std::endl;
    bool flag = 0;
    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W && event.key.code == sf::Keyboard::A) {
                    circle[1].move(-1, -1);
                }
                else if (event.key.code == sf::Keyboard::W && event.key.code == sf::Keyboard::D) {
                    circle[1].move(+1, -1);
                }

                else if (event.key.code == sf::Keyboard::S && event.key.code == sf::Keyboard::D) {
                    circle[1].move(+1, +1);
                }

                else if (event.key.code == sf::Keyboard::S && event.key.code == sf::Keyboard::A) {
                    circle[1].move(-1, +1);
                }

                else if (event.key.code == sf::Keyboard::W)
                {
                    circle[1].move(0, -1);
                }
                else if (event.key.code == sf::Keyboard::A)
                {
                    circle[1].move(-1, 0);

                }
                else if (event.key.code == sf::Keyboard::D)
                {
                    circle[1].move(+1, 0);

                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    circle[1].move(0, +1);

                }
            }

        }

        window.clear();
        window.draw(circle[1]);

        window.display();
    }

    return 0;
}