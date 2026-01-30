#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
  int rc = fork();

  if (rc < 0) {
    int fd = printf("Fork failed\n");
    exit(1);
  } 
  else if (rc == 0) { // child
    printf("pid %d- I am child\n", (int) getpid());
    char *envp[] = {NULL};
    // execl("/bin/ls", "ls", NULL); // static list
    // execlp("ls", "ls", NULL); // knows $PATH, executes file
    // execle("/bin/ls", "ls", NULL, envp); // + env

    char *args[] = {"ls", NULL};
    // execv("/bin/ls", args); // dynamic vector
    // execvp("ls", args);
    // execve("/bin/ls", args, envp);
    printf("Shouldn't print");
  } 
  else { // parent
    printf("pid %d- I am parent\n", (int) getpid());    
  }

  return 0;
}
