// shuffle cards
/* Given an integer n, create a vector of n integers in a random order */
// g++ shuffle.cpp
// change output:
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

auto shuffle(int n) {
  int r[n];// old fashioned vector. Could change to vector container later.
  int a[n];
  for (int j=0; j<n; j++) {
    int rNew = std::rand();
    //std::cout << "rNew " << rNew << std:: endl;
    r[j] = rNew;
    a[j] = j;
    for (int i=j; i>0; i--) {
      if (rNew < r[i-1]) {
        r[i] = r[i-1];
        a[i] = a[i-1];
        r[i-1] = rNew;
        a[i-1] = j;
      } else {
        break;
      }
    }

  }
  /* std::cout << "r         a " << std:: endl;
  for (int j=0; j<n; j++) {
    std::cout << r[j] <<"  " << a[j] << std:: endl;
  }
  */
  return a; // need to return the random vector
}

int main() {
  /* initialize random seed: */
  srand (time(NULL));
  int n=52;
  auto a = shuffle(n);
  std::cout << " a " << std:: endl;
  for (int j=0; j<n; j++) {
    std::cout << a[j] << std:: endl;
  }
}

