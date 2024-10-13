// shuffle cards
/* Given an integer n, create a vector of n integers in a random order */
// g++ shuffle.cpp
// change output:
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int shuffle(int n) {
  int r[n];// old fashioned vector. Could change to vector container later.
  int a[n];
  for (int j=0; j<n; j++) {
    int rNew = std::rand();
    std::cout << "rNew " << rNew << std:: endl;
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
  return n; // need to return the random vector
}

int main() {
  /* initialize random seed: */
  srand (time(NULL));
  int out = shuffle(5);
}

