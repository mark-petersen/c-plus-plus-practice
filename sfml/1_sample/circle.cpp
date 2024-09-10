#include <SFML/Graphics.hpp>
// g++ circle.cpp -I/usr/local/Cellar/sfml/2.6.1/include -o a.out -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);
    while (window.isOpen())
    {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear();
    window.draw(shape);
    window.display();
    }
}
//Moreira, Artur; Hansson, Henrik Vogelius; Haller, Jan. SFML Game Development (pp. 9-10). Packt Publishing. Kindle Edition. 
