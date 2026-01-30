#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define N 1000000

int main() {
  struct timeval start, end;
  gettimeofday(&start, NULL);

  for (int i = 0; i < N; i++) getpid();

  gettimeofday(&end, NULL);

  long seconds = end.tv_sec - start.tv_sec,
       useconds = end.tv_usec - start.tv_usec,
       total = seconds * 1000000 + useconds;

  printf("Total time: %ld us\n", total);
  printf("Avg time for a syscall= %.3f ns\n", (total * 1000.0) / N);
}