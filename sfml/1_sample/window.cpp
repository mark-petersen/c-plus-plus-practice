#include <SFML/Graphics.hpp>
// g++ window.cpp -I/usr/local/Cellar/sfml/2.6.1/include -o a.out -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics

 int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
         window.clear();
        window.display();
    }
     return 0;
}

