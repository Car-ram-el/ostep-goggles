#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf("hello there, (pid: %d)\n", (int) getpid());

  int rc = fork();
  if (rc < 0) { fprintf(stderr, "fork failed\n"); exit(1); }
  else if (rc == 0) {
    printf("I am a child process (pid: %d)\n", (int) getpid());

    char *childArgs[3];
    childArgs[0] = strdup("wc"); // program: word count
    childArgs[1] = strdup("p1.c"); // arg: file to count
    childArgs[2] = NULL; // end of []
    execvp(childArgs[0], childArgs); // runs word count
    printf("this shouldn't print");
   } else {
    int wc = wait(NULL);
    printf("I am parent of %d (wc: %d) (pid: %d)\n", rc, wc, (int) getpid());
  }
  return 0;
}