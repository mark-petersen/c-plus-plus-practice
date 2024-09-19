#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
// g++ subway.cpp -I/usr/local/Cellar/sfml/2.6.1/include -o a.out -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics -std=c++20

int XMax = 1000;
int iLen = 10;
int jLen = 10;

int c(float xIn) {
  int x = (xIn-0.5)*XMax/10.0;
  return x;
}

class Track {
  public:
    //Constructor
    Track() = default;
    
    void activate() {
      // asfdl
    }
    
  void viz(sf::RenderWindow &windowIn) {
    if (!m_exists) return;
  }

  private: 
    bool m_exists {false};
    int m_station1 {-1};
    int m_station2 {-1};
    int m_i1 {-1};
    int m_j1 {-1};
    int m_i2 {-1};
    int m_j2 {-1};
    float m_x1 {-1};
    float m_x2 {-1};
    float m_y1 {-1};
    float m_y2 {-1};
};

class Station {
  public:
    int i {-1};
    int j {-1};
    // Constructor
    Station() = default;

    Station(double x, double y, int shape) 
      : m_x{x}, m_y{y}, m_shape{shape}
    {
      std::cout << "Station constructor called with x="<<x<<" & y="<<y<<std::endl;
      m_exists = true;
    }
  
  bool exists() {
    return m_exists;
  }

  void viz(sf::RenderWindow &windowIn) {
    if (!m_exists) return;

    float r;
    sf::CircleShape shape;

    if (m_tourist) {
      r=18;
      shape.setRadius(r);
      shape.setPointCount(3);
      shape.setPosition(c(m_x)-r, c(m_y)-r);
      shape.setOutlineThickness(4.0);
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
      windowIn.draw(shape);
      r=18;
      shape.setRadius(r);
      shape.setPointCount(3);
      shape.setRotation(180);
      shape.setPosition(c(m_x+2*r), c(m_y));
      shape.setOutlineThickness(4.0);
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
      windowIn.draw(shape);
    }
    r = 16.0;
    shape.setRadius(r);
    shape.setPointCount(30);
    shape.setRotation(0);
    shape.setPosition(c(m_x)-r, c(m_y)-r);
    shape.setOutlineThickness(2.0);
    if (!m_home) {
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
    } else if (m_home==1) {
      shape.setFillColor(sf::Color::Green);
      shape.setOutlineColor(sf::Color::Green);
    } else if (m_home==2) {
      shape.setFillColor(sf::Color::Red);
      shape.setOutlineColor(sf::Color::Red);
    } else if (m_home==3) {
      shape.setFillColor(sf::Color::Magenta);
      shape.setOutlineColor(sf::Color::Magenta);
    } else if (m_home==4) {
      shape.setFillColor(sf::Color::Blue);
      shape.setOutlineColor(sf::Color::Blue);
    }
    windowIn.draw(shape);

    // circle
    if (m_shape==0) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(30);
      shape.setRotation(45);
      shape.setPosition(c(m_x), c(m_y)-1.4*r);
    }

    // triangle
    if (m_shape==3) {
      r=7.0;
      shape.setRadius(r);
      shape.setPointCount(3);
      shape.setRotation(0);
      shape.setPosition(c(m_x)-r, c(m_y)-r);
    }

    // square
    if (m_shape==4) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(4);
      shape.setRotation(45);
      shape.setPosition(c(m_x), c(m_y)-1.4*r);
    }

    // pentagon
    if (m_shape==5) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(5);
      shape.setRotation(0);
      shape.setPosition(c(m_x)-r, c(m_y)-r);
    }

    shape.setOutlineThickness(4.0);
    if (!m_home) {
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
    } else if (m_home==1) {
      shape.setFillColor(sf::Color::Green);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==2) {
      shape.setFillColor(sf::Color::Red);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==3) {
      shape.setFillColor(sf::Color::Magenta);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==4) {
      shape.setFillColor(sf::Color::Blue);
      shape.setOutlineColor(sf::Color::White);
    }
    windowIn.draw(shape);
}

    void init(int n) {
      j = n / 10; 
      i = n - 10*j;
      //std::cout << "n = "<<n<<" i = "<<i<<" j = "<<j<<std::endl;
    }

    void activate(int shape, int special) {
      m_exists = true;
      m_x = i + 1;
      m_y = j + 1;
      m_shape = shape;
      if (special==-1) {
        m_tourist = true;
      } else if (special > 0) {
        m_home = special;
      }
    }

    void info() {
      if (m_exists) {
        std::cout << "Station exists" << std::endl;
        std::cout << "x = " << m_x << std::endl;
        std::cout << "y = " << m_y << std::endl;
        std::cout << "shape = " << m_shape << std::endl;
      } else { 
        std::cout << "Station does not exist" << std::endl;
      }

    }

  private:
    bool m_exists {false};
    double m_x {-1.0};
    double m_y {-1.0};
    int m_shape {-1};
    bool m_tourist {false};
    int m_home {0};
};


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

    int stationDefs[100][4] {
       {  0, 0, 5, 0 }, 
       {  1, 0, 3, 0 }, 
       {  2, 0, 4, 0 }, 
       {  4, 0, 3, 0 }, 
       {  5, 0, 0, 0 }, 
       {  7, 0, 3, 0 }, 
       {  9, 0, 0, 0 }, 

       {  1, 1, 5, 0 }, 
       {  3, 1, 4, 0 }, 
       {  6, 1, 5,-1 }, 
       {  8, 1, 4, 0 }, 
       {  9, 1, 5, 0 }, 

       {  0, 2, 0, 0 }, 
       {  3, 2, 3, 1 }, 
       {  6, 2, 4, 0 }, 
       {  9, 2, 3, 0 }, 

       {  0, 3, 4,-1 }, 
       {  2, 3, 5, 0 }, 
       {  4, 3, 3, 0 }, 
       {  5, 3, 0,-1 }, 
       {  6, 3, 0, 0 }, 
       {  7, 3, 0, 2 }, 
       {  9, 3, 4, 0 },
// river
       {  1, 4, 3, 0 }, 
       {  2, 4, 4, 0 }, 
       {  4, 4, 5, 0 }, 
       {  5, 4, 4,-1 }, 
       {  8, 4, 5, 0 }, 

       {  0, 5, 5, 0 }, 
       {  2, 5, 4, 3 }, 
       {  3, 5, 3, 0 }, 
       {  5, 5, 0, 0 }, 

       {  3, 6, 5, 0 }, 
       {  4, 6, 3, 0 }, 
       {  6, 6, 4, 0 }, 
       {  7, 6, 3, 0 }, 
       {  9, 6, 3,-1 }, 

       {  0, 7, 0, 0 }, 
       {  2, 7, 4, 0 }, 
       {  3, 7, 0, 0 }, 
       {  5, 7, 5, 4 }, 
       {  8, 7, 0, 0 }, 
       {  9, 7, 5, 0 }, 

       {  1, 8, 0, 0 }, 
       {  6, 8, 5, 0 }, 
       {  8, 8, 3, 0 }, 

       {  0, 9, 3, 0 }, 
       {  1, 9, 4, 0 }, 
       {  3, 9, 5, 0 }, 
       {  4, 9, 0,-1 }, 
       {  5, 9, 3, 0 }, 
       {  7, 9, 0, 0 }, 
       {  9, 9, 4, 0 }, 

       { -1,-1,-1, 0 }
     };
    //auto stationDefs = InitStationDefs();
    //std::cout << "stationDefs" << stationDefs[5][0] << std::endl;

    std::array<Station, 100> Stations;
    for (int n=0; n<100; n++) {
      Stations[n].init(n);
    }

    for (int m=0; stationDefs[m][0]>-1; m++) {
      //std::cout << "m = " << m << "stationDefs[m] = " << stationDefs[m][0] << std::endl;
      int i = stationDefs[m][0];
      int j = stationDefs[m][1];
      int n = j*10+i;
      int shape = stationDefs[m][2];
      int special = stationDefs[m][3];
      Stations[n].activate(shape, special);
    }

    std::cout << "location 1" << std::endl;
    int iInc[8] {1,1,0,-1,-1,-1,0,1};
    std::cout << "iInc"<<iInc[0] << std::endl;
    int jInc[8] {0,1,1,1,0,-1,-1,-1};
    std::cout << "jInc"<<jInc[0] << std::endl;
    std::vector<Track> Tracks;
    std::cout << "location 1" << std::endl;
    //for (int n1=0; n1<100; n1++) {
    for (int n1=0; n1<10; n1++) {
    std::cout << "location 2" << std::endl;
      if (Stations[n1].exists()) {
    std::cout << "location 3" << std::endl;
        int i; int j; int n;
        for (int rot=0; rot<8; rot++) {
    std::cout << "location 4" << std::endl;
          i = Stations[n1].i;
          j = Stations[n1].j;
          std::cout << "n1,i,j,rot"<<n1<<" "<<i<<" "<<j<<" "<<rot<<" "<<std::endl;
          for (int iter=0; iter<10; iter++) {
            i += iInc[rot];
            if (i<0||i>=iLen) {
              break;
            }
            j += jInc[rot];
            if (j<0||j>=jLen) {
              break;
            }
            n = 10*j + i;
            std::cout << "iter, n,i,j,rot"<<iter<<" "<<n<<" "<<i<<" "<<j<<" "<<rot<<std::endl;
            if (Stations[n].exists()) {
              std::cout << "Station neig found!!! n1, n, i, j" << n1 <<" "<<n<<" "<<i<<" "<<j<<" "<<rot<<std::endl;
              break;
            }
          }
        }
      }

    }
    return 0;

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

    for (int n=0; n<100; n++) {
      Stations[n].viz(window);
    }

    window.display();
    }

}
