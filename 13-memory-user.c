#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 3) return 1;

  printf("pid %d- hello\n", (int) getpid());

  int memo = atoi(argv[1]), runtime = atoi(argv[2]);

  size_t bytes = (size_t)memo * 1024 * 1024;
  printf("bytes allocated= %zu bytes;\ttime to run= %d sec\n", bytes, runtime);

  int *arr = malloc(bytes);
  if (!arr) {
    perror("couldn't allocate memory");
    return 1;
  }

  __time_t start = time(NULL);
  size_t length = bytes / sizeof(int);

  while (time(NULL) - start < runtime)
    for (int i = 0; i < length; i++) arr[i]++; 
  
  printf("\n");
  free(arr);
  return 0;
}