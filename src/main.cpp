#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <snake.hpp>
#include <utility.hpp>
#include <iostream>

const int START_POSITION_X = 7;
const int START_POSITION_Y = 5;
const Direction START_DIRECTION = Direction::RIGHT;
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 960), "Snake window");
    // Load a sprite to display
    sf::RectangleShape rectangle(sf::Vector2f(1280, 960));
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-64);
    rectangle.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape snake(sf::Vector2f(64, 64));
    snake.setFillColor(sf::Color::Green);
    int x = START_POSITION_X;
    int y = START_POSITION_Y;
    snake.setPosition(x, y);
    Player myplayer(x, y, START_DIRECTION);

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
                        myplayer.SetDirection(Direction::UP);
                    } else if (event.key.code == sf::Keyboard::Down){
                        myplayer.SetDirection(Direction::DOWN);
                    } else if (event.key.code == sf::Keyboard::Left){
                        myplayer.SetDirection(Direction::LEFT);
                    } else if (event.key.code == sf::Keyboard::Right){
                        myplayer.SetDirection(Direction::RIGHT);
                    }
                    

                        
                    break;

                // we don't process other types of events
                default:
                    break;
            }
    
        }

        myplayer.UpdatePosition();
        x = ConvertToPixel(myplayer.GetPositionX());
        y = ConvertToPixel(myplayer.GetPositionY());
        snake.setPosition(x, y);
        

        // Clear screen
        window.clear(sf::Color::White);
        // Draw the rectangle
        window.draw(rectangle);
        // Draw the green square snake
        window.draw(snake);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}