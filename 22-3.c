#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main() {
  srand(time(NULL));

  // totally random reference trace
  // for (int i = 0; i < 10; i++) {
  //   int r = rand() % 10;
  //   printf("%d ", r);
  // }

  // trace with some locality
  for (int i = 0; i < 10; i++) {
    int r = rand() % 10;
    // 90%- choose from 1..5, 10%- 17..20
    if (r < 9) printf("%d ", rand() % 5 + 1);
    else printf("%d ", rand() % 4 + 17); 
  }
}