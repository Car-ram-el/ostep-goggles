#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int rc1 = fork();

  if (rc1 < 0) {
    int fd = printf("Fork failed\n");
    exit(1);
  } 
  else if (!rc1) { // children
    int wc = wait(NULL); // returns -1
    printf("pid %d\tchild %d\tI am child\n", (int) getpid(), wc);    
  } 
  else { // parent
    printf("pid %d\tI am parent\nrc1 %d\n", (int) getpid(), rc1);
  }

  return 0;
}
