#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
// g++ subway.cpp -I/usr/local/Cellar/sfml/2.6.1/include -o a.out -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-window -lsfml-system -lsfml-graphics -std=c++20

int XMax = 700;
int windowWidth = 1000;
int windowHeight=  950;
int iLen = 10;
int jLen = 10;
float stretch = XMax/10.0;

int c(float i) {
  // convert index to x-coordinate
  int x = (i+0.5)*XMax/10.0;
  return x;
}

int ind(float x) {
  // convert x-coordinate to index
  int i = x*10.0/XMax;
  return i;
}

class Track {
  public:
    //Constructor
    Track() = default;
    Track(int i1,int j1,int i2,int j2) :
      m_i1(i1), m_j1(j1), m_i2(i2), m_j2(j2)
    {
      //m_line[0].position = sf::Vector2f(c(i1), c(j1));
      //m_line[1].position = sf::Vector2f(c(i2), c(j2));
      //m_line[0].color  = sf::Color::Black;
      //m_line[1].color  = sf::Color::Black;
    }
    void info() {
      std::cout << "track: ("<<m_i1<<", "<<m_j1<<") to ( "<<m_i2<<", "<<m_j2<<")"<<std::endl;
    }
    void viz(sf::RenderWindow &windowIn) {
      sf::VertexArray m_line(sf::LineStrip, 2);
      m_line[0].position = sf::Vector2f(c(m_i1), c(m_j1));
      m_line[1].position = sf::Vector2f(c(m_i2), c(m_j2));
      sf::Color Grey(200,200,200);
      m_line[0].color = Grey;
      m_line[1].color = Grey;
      windowIn.draw(m_line);
    }

  private: 
    int m_station1 {-1};
    int m_station2 {-1};
    int m_i1 {-1};
    int m_j1 {-1};
    int m_i2 {-1};
    int m_j2 {-1};
};

class Station {
  public:
    // Constructor
    Station() = default;

    Station(int i, int j, int shape) 
      : m_i{i}, m_j{j}, m_shape{shape}
    {
      std::cout << "Station constructor called with i="<<i<<" & j="<<j<<std::endl;
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
      shape.setPosition(c(m_i)-r, c(m_j)-r);
      shape.setOutlineThickness(4.0);
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
      windowIn.draw(shape);
      r=18;
      shape.setRadius(r);
      shape.setRotation(60);
      shape.setPosition(c(m_i)+0.4*r, c(m_j)-1.4*r);
      windowIn.draw(shape);
    }
    r = 16.0;
    shape.setRadius(r);
    shape.setPointCount(30);
    shape.setRotation(0);
    shape.setPosition(c(m_i)-r, c(m_j)-r);
    shape.setOutlineThickness(2.0);
    if (!m_home) {
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
    } else if (m_home==1) {
      // set color to a private variable!
      sf::Color color(  0,193, 93); // dark green
      shape.setFillColor(color);
      shape.setOutlineColor(color);
    } else if (m_home==2) {
      sf::Color color(211,  0, 54); // red
      shape.setFillColor(color);
      shape.setOutlineColor(color);
    } else if (m_home==3) {
      sf::Color color(156,  0,223); // purple
      shape.setFillColor(color);
      shape.setOutlineColor(color);
    } else if (m_home==4) {
      sf::Color color(  0,151,222); // blue
      shape.setFillColor(color);
      shape.setOutlineColor(color);
    }
    windowIn.draw(shape);

    // circle
    if (m_shape==0) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(30);
      shape.setRotation(45);
      shape.setPosition(c(m_i), c(m_j)-1.4*r);
    }

    // triangle
    if (m_shape==3) {
      r=7.0;
      shape.setRadius(r);
      shape.setPointCount(3);
      shape.setRotation(0);
      shape.setPosition(c(m_i)-r, c(m_j)-r);
    }

    // square
    if (m_shape==4) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(4);
      shape.setRotation(45);
      shape.setPosition(c(m_i), c(m_j)-1.4*r);
    }

    // pentagon
    if (m_shape==5) {
      r=8.0;
      shape.setRadius(r);
      shape.setPointCount(5);
      shape.setRotation(0);
      shape.setPosition(c(m_i)-r, c(m_j)-r);
    }
    // wild
    if (m_shape==1) {
      r=2.0;
      shape.setRadius(r);
      shape.setPointCount(8);
      shape.setRotation(45);
      shape.setPosition(c(m_i), c(m_j)-1.4*r);
    }


    shape.setOutlineThickness(4.0);
    if (!m_home) {
      shape.setFillColor(sf::Color::White);
      shape.setOutlineColor(sf::Color::Black);
    } else if (m_home==1) {
      // set color to a private variable!
      sf::Color color(  0,193, 93); // dark green
      shape.setFillColor(color);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==2) {
      sf::Color color(211,  0, 54); // red
      shape.setFillColor(color);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==3) {
      sf::Color color(156,  0,223); // purple
      shape.setFillColor(color);
      shape.setOutlineColor(sf::Color::White);
    } else if (m_home==4) {
      sf::Color color(  0,151,222); // blue
      shape.setFillColor(color);
      shape.setOutlineColor(sf::Color::White);
    }
    windowIn.draw(shape);
}

    void init(int n) {
      m_j = n / 10; 
      m_i = n - 10*m_j;
      //std::cout << "n = "<<n<<" i = "<<i<<" j = "<<j<<std::endl;
    }

    void activate(int shape, int special) {
      m_exists = true;
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
        std::cout << "i = " << m_i << std::endl;
        std::cout << "j = " << m_j << std::endl;
        std::cout << "shape = " << m_shape << std::endl;
      } else { 
        std::cout << "Station does not exist" << std::endl;
      }

    }

  private:
    bool m_exists {false};
    int m_i {-1};
    int m_j {-1};
    int m_shape {-1};
    bool m_tourist {false};
    int m_home {0};
    //sf::Color color;
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
    lines[0].position = sf::Vector2f(c(x1-1), c(y1-1));
    lines[1].position = sf::Vector2f(c(x1-1), c(y2-1));
    lines[2].position = sf::Vector2f(c(x2-1), c(y2-1));
    lines[3].position = sf::Vector2f(c(x2-1), c(y1-1));
    lines[0].color  = colorIn;
    lines[1].color  = colorIn;
    lines[2].color  = colorIn;
    lines[3].color  = colorIn;
    windowIn.draw(lines);
}

void DrawBackground(sf::RenderWindow &window) {

// Draw regions
    sf::Color DarkYellow(253,200,23);
    Line( 3.5, 0.0, 3.5, 10.5, 1, window, DarkYellow);
    Line( 7.5, 0.0, 7.5, 10.5, 1, window, DarkYellow);
    Line(  0., 3.5, 10.5, 3.5, 1, window, DarkYellow);
    Line(  0., 7.5, 10.5, 7.5, 1, window, DarkYellow);
    Line( 0.5, 1.5,  1.5, 1.5, 1, window, DarkYellow);
    Line( 1.5, 0.5,  1.5, 1.5, 1, window, DarkYellow);
    Line( 9.5, 1.5, 10.5, 1.5, 1, window, DarkYellow);
    Line( 9.5, 0.5,  9.5, 1.5, 1, window, DarkYellow);
    Line( 0.5, 9.5,  1.5, 9.5, 1, window, DarkYellow);
    Line( 1.5, 9.5,  1.5,10.5, 1, window, DarkYellow);
    Line( 9.5, 9.5, 10.5, 9.5, 1, window, DarkYellow);
    Line( 9.5, 9.5,  9.5,10.5, 1, window, DarkYellow);

    // draw the river
    sf::VertexArray river(sf::LinesStrip, 6);
    river[0].position = sf::Vector2f(c(-0.5), c(3.5));
    river[1].position = sf::Vector2f(c( 2.2), c(3.5));
    river[2].position = sf::Vector2f(c( 3.8), c(5.4));
    river[3].position = sf::Vector2f(c( 5.2), c(5.4));
    river[4].position = sf::Vector2f(c( 6.2), c(4.4));
    river[5].position = sf::Vector2f(c( 9.5), c(4.4));
    for (int k=0; k<6; k++) {
      river[k].color  = sf::Color::Blue;
    }
    window.draw(river);

    // card area
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(windowWidth-XMax, XMax));
    sf::Color RightBlue(175,238,238);
    rectangle.setFillColor(RightBlue);
    rectangle.setOutlineThickness(0);
    rectangle.setPosition(XMax, 0);
    window.draw(rectangle);

    // scoring area
    rectangle.setSize(sf::Vector2f(windowWidth, windowHeight-XMax));
    sf::Color BottomYellow(255,232,128);
    rectangle.setFillColor(BottomYellow);
    rectangle.setOutlineThickness(0);
    rectangle.setPosition(0,XMax);
    window.draw(rectangle);
}


int main()
{
    std::cout << c(2) << std::endl;

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
       {  5, 3, 1,-1 }, 
       {  6, 3, 0, 0 }, 
       {  7, 3, 0, 2 }, 
       {  9, 3, 4, 0 },
// river
       {  1, 4, 3, 0 }, 
       {  2, 4, 4, 0 }, 
       {  4, 4, 5, 0 }, 
       {  5, 4, 4, 0 }, 
       {  8, 4, 5, 0 }, 

       {  0, 5, 5, 0 }, 
       {  2, 5, 4, 3 }, 
       {  4, 5, 0, 0 }, 
       {  7, 5, 0, 0 }, 

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

    int iInc[8] {1,1,0,-1,-1,-1,0,1};
    int jInc[8] {0,1,1,1,0,-1,-1,-1};
    std::vector<Track> Tracks;
    //for (int n1=0; n1<100; n1++) {
    int i; int j; int n;
    int nTracks = 0;
    for (int i1=0; i1<iLen; i1++) {
     for (int j1=0; j1<jLen; j1++) {
      int n1 = 10*j1+i1;
      if (Stations[n1].exists()) {
        //std::cout << "* Starting station i,j="<<" ("<<i1<<", "<<j1<<") "<<std::endl;
        for (int rot=0; rot<4; rot++) {
          i = i1;
          j = j1;
          //std::cout << "n1,i,j,rot"<<n1<<" "<<i<<" "<<j<<" "<<rot<<" "<<std::endl;
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
            //std::cout << "iter, n,i,j,rot"<<iter<<" "<<n<<" "<<i<<" "<<j<<" "<<rot<<std::endl;
            if (Stations[n].exists()) {
              Tracks.push_back(Track(i1,j1,i,j));
              nTracks +=1;
              break;
            }
          }
        }
       }
      }

    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Application");
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

    DrawBackground(window);

    for (int k=0; k<nTracks; k++) {
      Tracks[k].viz(window);
    }

    for (int n=0; n<100; n++) {
      Stations[n].viz(window);
    }

    window.display();
    // left click...
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      // get global mouse position
    sf::Vector2i position = sf::Mouse::getPosition(  window	);
    //std::cout<< "mouse click!" << std::endl;
    std::cout<< "mouse location: "<<ind(position.x) << ", "<< ind(position.y) <<std::endl;
      
      // set mouse position relative to a window
      //sf::Mouse::setPosition(sf::Vector2i(100, 200), window);
    }
    }

    return 0;
}
