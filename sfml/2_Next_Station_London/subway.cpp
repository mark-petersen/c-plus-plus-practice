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

void PlaceStation(float x1, float y1, int ShapeIn,
  sf::RenderWindow &windowIn) {
    sf::VertexArray lines(sf::LinesStrip, 4);

    float r;
    sf::CircleShape shape;

    r=16.0;
    shape.setRadius(r);
    shape.setPointCount(30);
    shape.setPosition(c(x1)-r, c(y1)-r);
    shape.setOutlineThickness(2.0);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    windowIn.draw(shape);

    // circle
    if (ShapeIn==0) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(30);
      shape.setRotation(45);
      shape.setPosition(c(x1), c(y1)-1.4*r);
    }

    // triangle
    if (ShapeIn==3) {
      r=7.0;
      shape.setRadius(r);
      shape.setPointCount(3);
      shape.setRotation(0);
      shape.setPosition(c(x1)-r, c(y1)-r);
    }

    // square
    if (ShapeIn==4) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(4);
      shape.setRotation(45);
      shape.setPosition(c(x1), c(y1)-1.4*r);
    }

    // pentagon
    if (ShapeIn==5) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(5);
      shape.setRotation(0);
      shape.setPosition(c(x1)-r, c(y1)-r);
    }

    shape.setOutlineThickness(4.0);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    windowIn.draw(shape);
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

    Line( 3.5, 0.0, 3.5, 10.5, 1, window, sf::Color::Yellow);
    Line( 7.5, 0.0, 7.5, 10.5, 1, window, sf::Color::Yellow);
    Line(  0., 3.5, 10.5, 3.5, 1, window, sf::Color::Yellow);
    Line(  0., 7.5, 10.5, 7.5, 1, window, sf::Color::Yellow);
    Line( 0.5, 1.5, 1.5, 1.5, 1, window, sf::Color::Yellow);
    Line( 1.5, 0.5, 1.5, 1.5, 1, window, sf::Color::Yellow);
    Line( 9.5, 1.5,10.5, 1.5, 1, window, sf::Color::Yellow);
    Line( 9.5, 0.5, 9.5, 1.5, 1, window, sf::Color::Yellow);
    Line( 0.5, 9.5, 1.5, 9.5, 1, window, sf::Color::Yellow);
    Line( 1.5, 9.5, 1.5,10.5, 1, window, sf::Color::Yellow);
    Line( 9.5, 9.5,10.5, 9.5, 1, window, sf::Color::Yellow);
    Line( 9.5, 9.5, 9.5,10.5, 1, window, sf::Color::Yellow);

    PlaceStation(  1, 1, 5, window);
    PlaceStation(  2, 1, 3, window);
    PlaceStation(  3, 1, 4, window);
    PlaceStation(  5, 1, 3, window);
    PlaceStation(  6, 1, 0, window);
    PlaceStation(  8, 1, 3, window);
    PlaceStation( 10, 1, 0, window);

    PlaceStation(  2, 2, 5, window);
    PlaceStation(  4, 2, 4, window);
    PlaceStation(  7, 2, 5, window);
    PlaceStation(  9, 2, 4, window);
    PlaceStation( 10, 2, 5, window);

    PlaceStation(  1, 3, 0, window);
    PlaceStation(  4, 3, 3, window);
    PlaceStation(  7, 3, 4, window);
    PlaceStation( 10, 3, 3, window);

    PlaceStation(  1, 4, 4, window);
    PlaceStation(  3, 4, 5, window);
    PlaceStation(  5, 4, 3, window);
    PlaceStation(  6, 4, 0, window);
    PlaceStation(  7, 4, 0, window);
    PlaceStation(  8, 4, 0, window);
    PlaceStation( 10, 4, 4, window);

    window.display();
    }
}
