#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <snake.hpp>
#include <utility.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <deque>
#include <string>

const int START_POSITION_X = 7;
const int START_POSITION_Y = 5;
const Direction START_DIRECTION = Direction::RIGHT;
const int APPLE_START_X = 15;
const int APPLE_START_Y = 7;
const int WIDTH = 20;
const int HEIGHT = 15;
const float MOVE_TIME = 150.0f;

int main(int nNumberofArgs, char* args[])
{
    int height = HEIGHT;
    float multiple = 1.0f;
    
    float move_time = MOVE_TIME;
    int width = WIDTH;
    // Check first argument
    if (nNumberofArgs >= 2) {
        width = std::atoi(args[1]);
        multiple = width/WIDTH;
        height = static_cast<int>(height * multiple);
    } 
    
    // Check second argument
    if (nNumberofArgs == 3) {
        move_time = std::atof(args[2]);
    }
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Snake window");
    // Create a rectangle snake to display
    sf::RectangleShape rectangle(sf::Vector2f(1280, 960));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-64);
    rectangle.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape square(sf::Vector2f(64/multiple, 64/multiple));
    square.setFillColor(sf::Color::Green);

    int x = START_POSITION_X * multiple;
    int y = START_POSITION_Y * multiple;
    // Define Player snake
    Player snake(x, y, START_DIRECTION, move_time);
    sf::Clock clock;

    sf::Texture texture;
    if (!texture.loadFromFile("../data/apple.png")){
        return EXIT_FAILURE;
    }
    sf::Sprite apple;
    apple.setTexture(texture);
    int a = APPLE_START_X * multiple;
    int b = APPLE_START_Y * multiple;
    apple.setScale(1/multiple, 1/multiple);
    //std::cout << "Resize Apple Code" << std::endl;
    
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
        
        bool collision = snake.UpdatePosition(clock.restart().asMilliseconds(), multiple);
        //std::cout << "Update position is fine" << std::endl;
        if (collision == true){
            a = APPLE_START_X * multiple;
            //std::cout << "Reset apple X position" << std::endl;
            b = APPLE_START_Y * multiple;
            //std::cout << "Reset apple Y position" << std::endl;
        }
        std::deque<Position> queue = snake.GetPositions();
        int queueSize = queue.size();
        //std::vector<square> squareVector;
        
        x = snake.GetPositionX();
        y = snake.GetPositionY();
        
        if (x == a & y == b){
            snake.IncrementLength();

            srand (time(NULL));
            a = rand() % static_cast<int>(18 * multiple) + 1 * multiple;
            //std::cout << "Find the random position for Apple X" << std::endl;
            b = rand() % static_cast<int>(13 * multiple) + 1 * multiple; 
            //std::cout << "Find the random position for Apple Y" << std::endl;  
        }

        int appleX = static_cast<int>(ConvertToPixel(a)/multiple);
        int appleY = static_cast<int>(ConvertToPixel(b)/multiple);
        apple.setPosition(appleX, appleY);
        //std::cout << "Set up position for apple" << std::endl;

        // Clear screen
        window.clear(sf::Color::White);
        // Draw the rectangle
        window.draw(rectangle);
        // Draw the green square snake
        for (int i = 0; i < queueSize; ++i){
            square.setPosition(static_cast<int>(ConvertToPixel(queue[i].x)/multiple), static_cast<int>(ConvertToPixel(queue[i].y)/multiple));
            //std::cout << "Set up position for Snake square" << std::endl;
            window.draw(square);
        }
        // Draw the sprite of apple
        window.draw(apple);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}