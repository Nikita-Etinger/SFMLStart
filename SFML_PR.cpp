#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(nullptr));

    const int windowWidth = 800;
    const int windowHeight = 600;
    const int ballCountHorizontal = 10;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), " Balls");
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> balls;

    float ballRadius = float(windowWidth) / (ballCountHorizontal * 2);
    float ballSpacing = ballRadius * 2; //интервал

    int ballCountVertical = int(windowHeight / ballSpacing);

    for (int row = 0; row < ballCountVertical; ++row) {
        for (int col = 0; col < ballCountHorizontal; ++col) {
            sf::CircleShape ball(ballRadius);
            ball.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            ball.setPosition(col * ballSpacing, row * ballSpacing);
            balls.push_back(ball);
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Equal) { // '+' key
                    sf::CircleShape ball(ballRadius);
                    ball.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
                    ball.setPosition(float(balls.size() % ballCountHorizontal) * ballSpacing,
                        float(balls.size() / ballCountHorizontal) * ballSpacing);
                    balls.push_back(ball);
                }
                if (event.key.code == sf::Keyboard::Dash && !balls.empty()) { // '-' key
                    balls.pop_back();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (auto it = balls.begin(); it != balls.end(); ++it) {
                        if (it->getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                            //проверка, что координаты нажатия мыши совпадают с конкретным шаром
                            it = balls.erase(it);
                            for (; it != balls.end(); ++it) {
                                //переместить все оставшиеся шары
                                int col = (it - balls.begin()) % ballCountHorizontal;
                                int row = (it - balls.begin()) / ballCountHorizontal;
                                it->setPosition(col * ballSpacing, row * ballSpacing);
                            }
                            break;
                        }
                    }
                }
            }
        }

        window.clear();
        for (const auto& ball : balls) {
            window.draw(ball);
        }
        window.display();
    }

    return 0;
}