#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#define PORT 8070
#define SA struct sockaddr

// server returns current time / file content
void talk(int socketfd) {
  char* req = "README.md";
  char buffer[2048];

  // write(socketfd, req, strlen(req) + 1);
  // sleep(2);
  // int n = read(socketfd, buffer, sizeof(buffer) - 1);
  // buffer[n] = '\0';

  write(socketfd, req, strlen(req) + 1);
  sleep(2);
  int n;
  while ((n = read(socketfd, buffer, sizeof(buffer))) > 0) {
    write(STDOUT_FILENO, buffer, n);
  }
  printf("buffer: %s\n", buffer);
}

int main(int argc, char const *argv[]){
  int socketfd, connectionfd;
  struct sockaddr_in serveraddr, cli;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    printf("client: socket creation failed\n");
    exit(1);
  }

  printf("client: socket created\n");
  bzero(&serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(PORT);

  if (connect(socketfd, (SA*)&serveraddr, sizeof(serveraddr))) {
    printf("client: connection failed\n");
    exit(1);
  }

  printf("client: connected\n");
  talk(socketfd);
  close(socketfd);
}