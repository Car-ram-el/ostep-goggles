#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int pipefd[2]; pipe(pipefd);

  int rc1 = fork();

  if (!rc1) { // child writes to pipe
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO); // stdout -> pipe write
    close(pipefd[1]);
    printf("pid %d\tI am child1\n", (int) getpid());
    exit(0);
  }

  int rc2 = fork();
  if (!rc2) { // reads from pipe
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO); // stdin -> pipe read
    close(pipefd[0]);
    char buf[128];
    fgets(buf, sizeof(buf), stdin);
    printf("pid %d\tI am child2.\nReceived: %s", (int) getpid(), buf);
    exit(0);
  }

  return 0;
}