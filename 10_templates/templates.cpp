// g++ templates.cpp
// ./a.out
#include <iostream>

size_t MPAS_VH = 1;
size_t MPAS_HV = 2;
size_t QUAD_VH = 3;
size_t QUAD_HV = 4;

// headers
void RHS();
void term1();
void term2();

// functions
void RHS() {
  std::cout << "RHS"<< std::endl;
  term1();
  term2();
}

void term1() {
  std::cout << "term 1"<< std::endl;
}

void term2() {
  std::cout << "term 2"<< std::endl;
}

int main() {
  std::cout << "Hello"<< std::endl;
  RHS();
};
