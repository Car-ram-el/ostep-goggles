#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sched.h>
#include <pthread.h>
#include <string.h>

const int PAGESIZE = 4096;

int main (int argc, char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Invalid arguments passed.\n");
    exit(1);
  }

  // set cpu affinity (pin a thread to avoid tlb bounces between cpus)
  cpu_set_t set;
  CPU_ZERO(&set);
  CPU_SET(0, &set); // use cpu 0
  sched_setaffinity(0, sizeof(set), &set);

  int numOfPages = atoi(argv[1]), numOfTrials = atoi(argv[2]),
      aSize = numOfPages * PAGESIZE;
  int *a = (int*) malloc(aSize);
  if (!a) {
    perror("malloc");
    exit(1);
  }
  int jump = PAGESIZE / sizeof(int); // ints per page => jump to the next page

  // init array to avoid demand zeroing or page faults
  memset(a, 0, aSize);

  struct timeval start, end;

  gettimeofday(&start, NULL);
  for(int i = 0; i < numOfTrials; ++i) {
    for (int j = 0; j < numOfPages * jump; j += jump) a[j]++;
  }
  gettimeofday(&end, NULL);
  
  long sec = end.tv_sec - start.tv_sec, usec = end.tv_usec - start.tv_usec,
        totalTime = sec * 1000000 + usec;
  double avgAccessTime = (double)totalTime * 1000.0 / (numOfPages * numOfTrials);
  
  printf("Pages: %d\tAccessTime: %.3f nsec/page\n", numOfPages, avgAccessTime);

  free(a);  
}