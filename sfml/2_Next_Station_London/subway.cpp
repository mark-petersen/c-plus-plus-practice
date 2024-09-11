#include <SFML/Graphics.hpp>
#include <iostream>
// g++ subway.cpp  -I/usr/local/Cellar/sfml/2.6.1/include -o a.out -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics 

int XMax = 1000;

int c(float xIn) {
  int x = (xIn-0.5)*XMax/10.0;
  return x;
}

void VLine(float xIn, sf::RenderWindow &windowIn, sf::Color colorIn) {
    sf::VertexArray lines(sf::LinesStrip, 4);
    lines[0].position = sf::Vector2f(c(xIn)-1.0, 0);
    lines[1].position = sf::Vector2f(c(xIn)-1.0, XMax);
    lines[2].position = sf::Vector2f(c(xIn)+1.0, XMax);
    lines[3].position = sf::Vector2f(c(xIn)+1.0, 0);
    lines[0].color  = colorIn;
    lines[1].color  = colorIn;
    lines[2].color  = colorIn;
    lines[3].color  = colorIn;
    windowIn.draw(lines);
}

void Line(float x1, float y1, float x2, float y2, float PW,
  sf::RenderWindow &windowIn, sf::Color colorIn) {
    sf::VertexArray lines(sf::LinesStrip, 4);
    lines[0].position = sf::Vector2f(c(x1)-PW, c(y1)-PW);
    lines[1].position = sf::Vector2f(c(x1)-PW, c(y2)+PW);
    lines[2].position = sf::Vector2f(c(x2)+PW, c(y2)+PW);
    lines[3].position = sf::Vector2f(c(x2)+PW, c(y1)-PW);
    lines[0].color  = colorIn;
    lines[1].color  = colorIn;
    lines[2].color  = colorIn;
    lines[3].color  = colorIn;
    windowIn.draw(lines);
}


int main()
{
    std::cout << c(2) << std::endl;
    sf::RenderWindow window(sf::VideoMode(XMax, XMax), "SFML Application");
    window.setPosition(sf::Vector2i(10, 10));

    while (window.isOpen())
    {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    window.clear(sf::Color::White);

    sf::CircleShape shape;
    shape.setRadius(4.f);
    shape.setPosition(c(2), c(2));
    shape.setFillColor(sf::Color::Cyan);
    window.draw(shape);

    Line(3.5, 0., 5.5, 10., 1, window, sf::Color::Yellow);
    Line(7.5, 0., 7.5, 10., 1, window, sf::Color::Yellow);

    window.display();
    }
}
