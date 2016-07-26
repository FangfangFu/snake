#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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
    int x = 640;
    int y = 448;
    snake.setPosition(x, y);
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
                    if (event.key.code == sf::Keyboard::Left){
                        x -= 64;
                        if (x < 64){
                            x = 64;
                        }
                    } else if (event.key.code == sf::Keyboard::Right){
                        x += 64;
                        if (x > 1152){
                            x = 1152;
                        }
                    } else if (event.key.code == sf::Keyboard::Up){
                        y -= 64;
                        if (y < 64){
                            y = 64;
                        }
                    } else if (event.key.code == sf::Keyboard::Down){
                        y += 64;
                        if (y > 832){
                            y = 832;
                        }
                    }
                        snake.setPosition(x, y);

                        
                    break;

                // we don't process other types of events
                default:
                    break;
            }
    
        }
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