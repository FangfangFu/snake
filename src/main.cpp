// This program is about snake eating apple and growing longer; it dies if snake eats itself or hit the wall
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

const int START_POSITION_X = 7;                        // Snake initial x-axis position
const int START_POSITION_Y = 5;                        // Snake initial y-axis position
const Direction START_DIRECTION = Direction::RIGHT;    // Snake initial moving direction
const int APPLE_START_X = 15;                          // Apple initial x-axis position
const int APPLE_START_Y = 7;                           // Apple initial y-axis position
const int WIDTH = 20;                                  // Default x axis length in game coordinate
const int HEIGHT = 15;                                 // Default y axis length in game coordinate
const float MOVE_TIME = 150.0f;                        // Default move time for moving 1 game unit

int main(int nNumberofArgs, char* args[])
{
    int height = HEIGHT;
    float multiple = 1.0f;
    
    float move_time = MOVE_TIME;
    int width = WIDTH;
    // Check first argument
    if (nNumberofArgs >= 2) {
        width = std::atoi(args[1]);
        multiple = static_cast<float>(width)/static_cast<float>(WIDTH);
        height = static_cast<int>(height * multiple);
    } 
    
    // Check second argument
    if (nNumberofArgs == 3) {
        move_time = std::atof(args[2]);
    }
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Snake window");
    // Create a rectangle window to display
    sf::RectangleShape rectangle(sf::Vector2f(1280, 960));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-64);
    rectangle.setOutlineColor(sf::Color::Blue);
    // Create a green square element of a snake
    sf::RectangleShape square(sf::Vector2f(64/multiple, 64/multiple));
    square.setFillColor(sf::Color::Green);
    // Start position for snake
    int x = START_POSITION_X * multiple;
    int y = START_POSITION_Y * multiple;
    // Define Player snake
    Player snake(x, y, START_DIRECTION, move_time);
    sf::Clock clock;
    // Upload a texture of an apple
    sf::Texture texture;
    if (!texture.loadFromFile("../data/apple.png")){
        return EXIT_FAILURE;
    }
    // Create a apple sprite with that apple texture
    sf::Sprite apple;
    apple.setTexture(texture);
    apple.setScale(1/multiple, 1/multiple);
    // Initial position for apple
    int a = APPLE_START_X * multiple;
    int b = APPLE_START_Y * multiple;
    
    //Window loop
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
        // When snake hits the wall or eats itself, the game will restart
        bool collision = snake.UpdatePosition(clock.restart().asMilliseconds(), multiple);
        if (collision == true){
            a = APPLE_START_X * multiple;
            b = APPLE_START_Y * multiple;
        }
        // Get a queue of squares to prepare for latter snake drawing
        std::deque<Position> queue = snake.GetPositions();
        int queueSize = queue.size();
        
        x = snake.GetPositionX();
        y = snake.GetPositionY();
        
        // When the apple is eaten, the snake becomes longer and apple would be randomly reput
        if (x == a & y == b){
            snake.IncrementLength();

            srand (time(NULL));
            a = rand() % static_cast<int>(18 * multiple) + 1 * multiple;
            b = rand() % static_cast<int>(13 * multiple) + 1 * multiple;   
        }
        // Set up apple position for each iteration
        int appleX = static_cast<int>(ConvertToPixel(a)/multiple);
        int appleY = static_cast<int>(ConvertToPixel(b)/multiple);
        apple.setPosition(appleX, appleY);

        // Clear screen
        window.clear(sf::Color::White);
        // Draw the rectangle
        window.draw(rectangle);
        // Draw the green square snake
        for (int i = 0; i < queueSize; ++i){
            square.setPosition(static_cast<int>(ConvertToPixel(queue[i].x)/multiple), static_cast<int>(ConvertToPixel(queue[i].y)/multiple));
            window.draw(square);
        }
        // Draw the sprite of apple
        window.draw(apple);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}