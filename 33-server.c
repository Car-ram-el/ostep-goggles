// server that can accept, serve tcp connections

#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <aio.h>

#define PORT 8070
#define SA struct sockaddr
#define minFD 0
#define maxFD 7
#define max(a,b) ((a) > (b) ? (a) : (b))

void talk(int connectionfd, char *req) {
  char buffer[1024];

  // get current time
  // struct timeval start;
  // gettimeofday(&start, NULL);
  // long curTime = start.tv_sec * 1000000 + start.tv_usec;
  // snprintf(buffer, sizeof(buffer), "time = %ld\n", curTime);
  // printf("response: %ld\n", curTime);

  // get file content
  int filefd = open(req, O_RDONLY);
  if (filefd < 0) {
    snprintf(buffer, sizeof(buffer), "open() err %d: %s\n", errno, strerror(errno));
    write(connectionfd, buffer, strlen(buffer));
    return;
  }
  int n;
  while ((n = read(filefd, buffer, sizeof(buffer))) > 0) write(connectionfd, buffer, n);
  close(filefd);
}

int main(int argc, char const *argv[]) {
  int socketfd, connectionfd;
  socklen_t len;
  struct sockaddr_in serveraddr, clientaddr;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    printf("server: socket creation failed\n");
    exit(1);
  }
  
  bzero(&serveraddr, sizeof(serveraddr));

  // assign ip, port
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(PORT);

  // even after the server exits, kernel might reserve the port. Enable address reuse
  int opt = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // bind new socket to given ip, verify
  if (bind(socketfd, (SA*)&serveraddr, sizeof(serveraddr))) {
    perror("bind");
    exit(1);
  }

  if (listen(socketfd, 7)) {
    perror("listen");
    exit(1);
  }

  printf("socket up\n");

  // select() code
  fd_set mainFDs, readFDs;
  int maxfd;
  FD_ZERO (&mainFDs);
  FD_SET(socketfd, &mainFDs);
  maxfd = socketfd;

  while (1) {
    readFDs = mainFDs;
    int readySet = select(maxfd + 1, &readFDs, NULL, NULL, NULL);
    if (readySet < 0) perror("select");

    for(int fd = 0; fd < maxfd + 1; ++fd) {
      if (FD_ISSET(fd, &readFDs)) {
        printf("fd %d\n", fd);
        if (fd == socketfd) { // add new connection to the listening socket
          len = sizeof(clientaddr);
          int connectionfd = accept(fd, (SA*)&clientaddr, &len);
          if (connectionfd == -1) {
            perror("accept");
            continue;
          }
          printf("connectionfd %d\n", connectionfd);
          FD_SET(connectionfd, &mainFDs);
          maxfd = max(maxfd, connectionfd);
        }
        else {
          char buff[2048];
          int n = read(fd, buff, sizeof(buff) - 1);
          if (n <= 0) {
            FD_CLR(fd, &mainFDs);
            close(fd);
          }
          else {
            buff[n] = '\0';
            talk(fd, buff);
          }
        }
      }
    }
  }

  close(socketfd);
}