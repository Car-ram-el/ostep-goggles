#include <stdlib.h>
#include <stdio.h>

int main() {
  printf("helloo\n");
  int *data = malloc(100 * sizeof(int));
  free(&data[4]);

  printf("data[77] = %d", data[77]);
}
