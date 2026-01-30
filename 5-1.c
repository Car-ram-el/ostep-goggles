#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
  // close(STDOUT_FILENO);
  // int fd = open("./5-1.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  int pipefd[2]; // 0- read end, 1- write end
  pipe(pipefd);

  int rc = fork();

  if (rc < 0) {
    int fd = printf("Fork failed\n");
    exit(1);
  } else if (rc == 0) { // child
    close(pipefd[0]); // doesn't read
    printf("hello\n");
    write(pipefd[1], "x", 1); // write to signal- unblock parent's read
    close(pipefd[1]);
  } else { // parent
    close(pipefd[1]); // doesn't write
    char buf;
    read(pipefd[0], &buf, 1);
    printf("goodbye\n");
    close(pipefd[0]);
  }

  return 0;
}
