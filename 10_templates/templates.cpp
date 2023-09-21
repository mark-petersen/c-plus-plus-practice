// g++ templates.cpp
// ./a.out
#include <iostream>

constexpr size_t MPAS_VH = 1;
constexpr size_t MPAS_HV = 2;
constexpr size_t QUAD_VH = 3;
constexpr size_t QUAD_HV = 4;

// headers
template <size_t MT> void RHS();

template <size_t MT> void term1();

template <> void term1<MPAS_VH>();

template <> void term1<QUAD_VH>();

void term2();

// functions
int main() {
  std::cout << "Hello, type 1-4" << std::endl;
  size_t MT_in;
  std::cin >> MT_in;
  if (MT_in == MPAS_VH) {
    RHS<MPAS_VH>();
  } else if (MT_in == QUAD_VH) {
    RHS<QUAD_VH>();
  } else if (MT_in == MPAS_HV) {
    RHS<MPAS_HV>();
  } else if (MT_in == QUAD_HV) {
    RHS<QUAD_HV>();
  } else {
    std::cout << "need 1-4" << std::endl;
  }
};

template <size_t MT> void RHS() {
  std::cout << "RHS" << std::endl;
  term1<MT>();
  term2();
}

template <size_t MT> void term1() {
  std::cout << "term 1 MT = " << MT << std::endl;
}

template <> void term1<MPAS_VH>() {
  std::cout << "term 1 MPAS_VH" << std::endl;
}

template <> void term1<QUAD_VH>() {
  std::cout << "term 1 QUAD_VH" << std::endl;
}

void term2() { std::cout << "term 2" << std::endl; }
