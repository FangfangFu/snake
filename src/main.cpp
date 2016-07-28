#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <snake.hpp>
#include <utility.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <deque>

const int START_POSITION_X = 7;
const int START_POSITION_Y = 5;
const Direction START_DIRECTION = Direction::RIGHT;
const int APPLE_START_X = 15;
const int APPLE_START_Y = 7;
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Snake window");
    // Create a rectangle snake to display
    sf::RectangleShape rectangle(sf::Vector2f(1280, 960));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-64);
    rectangle.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape square(sf::Vector2f(64, 64));
    square.setFillColor(sf::Color::Green);
    int x = START_POSITION_X;
    int y = START_POSITION_Y;

    Player snake(x, y, START_DIRECTION);
    sf::Clock clock;

    sf::Texture texture;
    if (!texture.loadFromFile("../data/apple.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite apple;
    apple.setTexture(texture);
    int a = APPLE_START_X;
    int b = APPLE_START_Y;
    

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                // key pressed
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Up){
                        snake.SetDirection(Direction::UP);
                    } else if (event.key.code == sf::Keyboard::Down){
                        snake.SetDirection(Direction::DOWN);
                    } else if (event.key.code == sf::Keyboard::Left){
                        snake.SetDirection(Direction::LEFT);
                    } else if (event.key.code == sf::Keyboard::Right){
                        snake.SetDirection(Direction::RIGHT);
                    }

                    break;

                // we don't process other types of events
                default:
                    break;
            }
    
        }
        
        bool collision = snake.UpdatePosition(clock.restart().asMilliseconds());
        if (collision == true){
            a = APPLE_START_X;
            b = APPLE_START_Y;
        }
        std::deque<Position> queue = snake.GetPositions();
        int queueSize = queue.size();
        //std::vector<square> squareVector;
        
        x = snake.GetPositionX();
        y = snake.GetPositionY();
        
        if (x == a & y == b){
            snake.IncrementLength();

            srand (time(NULL));
            a = rand() % 18 + 1;
            b = rand() % 13 + 1;   
        }
        apple.setPosition(ConvertToPixel(a), ConvertToPixel(b));
        

        // Clear screen
        window.clear(sf::Color::White);
        // Draw the rectangle
        window.draw(rectangle);
        // Draw the green square snake
        for (int i = 0; i < queueSize; ++i){
            square.setPosition(ConvertToPixel(queue[i].x), ConvertToPixel(queue[i].y));
            window.draw(square);
        }
        // Draw the sprite of apple
        window.draw(apple);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}